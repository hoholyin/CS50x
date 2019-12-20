from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *
import datetime

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    portfolio = db.execute("SELECT symbol, quantity FROM portfolio WHERE id = :id", id=session["user_id"])
    
    total_value = 0
    for name in portfolio:
        quantity = name["quantity"]
        stock = lookup(name["symbol"])
        currentprice = float(stock["price"])
        total = float(quantity)*currentprice
        
        total_value = total_value +total
        db.execute("UPDATE portfolio SET current=:current WHERE id=:id AND symbol=:symbol", id=session["user_id"], current=currentprice, symbol=stock["symbol"]) 
        db.execute("UPDATE portfolio SET total=:total WHERE id=:id AND symbol=:symbol", id=session["user_id"], total=total, symbol=stock["symbol"]) 

    newcash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        
    total_value = total_value+newcash[0]["cash"]
    
   
    newportfolio = db.execute("SELECT * FROM portfolio WHERE id=:id", id=session["user_id"])
    shares = db.execute("SELECT quantity FROM portfolio WHERE id=:id", id=session["user_id"])

    return render_template("index.html", shares=shares, portfolio=newportfolio, cash=format(newcash[0]["cash"], '.2f'), total=format(total_value, '.2f'))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        
        if not request.form.get("symbol"):
            return apology("Please input symbol")
        
        stock=lookup(request.form.get("symbol"))
        if not stock:
            return apology("Symbol does not exist")
        try:    
            quantity=int(request.form.get("quantity"))
            if quantity<1:
                return apology("Invalid Quantity")
        except:
            return apology("Invalid Quantity")
            
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        
        if not cash or float(cash[0]["cash"])<(quantity*(stock["price"])):
            return apology("Not enough money!")
            
        
        else:
            db.execute("UPDATE users SET cash = :newcash WHERE id = :id", newcash=cash[0]["cash"]-(float(quantity)*(stock["price"])), id=session["user_id"])

            db.execute("INSERT INTO history (id, shares, quantity, total, datetime, buysell) VALUES (:id, :shares, :quantity, :total, :t, :buy)", id=session["user_id"], shares=stock["symbol"], quantity=quantity, total=(quantity*(stock["price"])), t=(str(datetime.datetime.utcnow())), buy="buy")
            
            checkstock = db.execute("SELECT quantity FROM portfolio WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=stock["symbol"])
            if not checkstock:
                db.execute("INSERT INTO portfolio (name, symbol, price, quantity, total, id, lasttransaction) VALUES (:name, :symbol, :price, :quantity, :total, :id, :t)", name=stock["name"], symbol=stock["symbol"], price=stock["price"], quantity=quantity, total=(quantity*(stock["price"])), id=session["user_id"], t=(str(datetime.datetime.utcnow())))
            else:
                oldquantity = db.execute("SELECT quantity FROM portfolio WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=stock["symbol"])
                oldtotal = db.execute("SELECT total FROM portfolio WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=stock["symbol"])
                db.execute("UPDATE portfolio SET quantity=:quantity WHERE id = :id AND symbol = :symbol", quantity=float(oldquantity[0]["quantity"])+quantity, id=session["user_id"], symbol=stock["symbol"])
                db.execute("UPDATE portfolio SET total=:total WHERE id = :id AND symbol = :symbol", total=float(oldtotal[0]["total"])+(quantity*(stock["price"])), id=session["user_id"], symbol=stock["symbol"])
                db.execute("UPDATE portfolio SET lasttransaction=:t WHERE id = :id AND symbol = :symbol", t=(str(datetime.datetime.utcnow())), id=session["user_id"], symbol=stock["symbol"])
                
        return redirect(url_for("index"))    

    #clicking a link or redirect to come to buy
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    portfolio = db.execute("SELECT * FROM history WHERE id = :id ORDER BY datetime DESC", id=session["user_id"])

    return render_template("history.html", portfolio=portfolio)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        a=lookup(request.form.get("symbol"))
        if not a:
            return apology("Quote not available")
        
        return render_template("quoted.html", stock=a)
            
    #clicking a link or redirect to come to quote
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    if request.method == "POST":
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
        
        # ensure passwords match    
        elif request.form.get("password") != request.form.get("passwordagain"):
            return apology("Passwords do not match")
        
    
        registered = db.execute("INSERT INTO users (username,hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=pwd_context.hash(request.form.get("password")))

        if not registered:
            return apology("Username Taken")
        else:
            return redirect(url_for("index"))
            
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    #if came from link
    if request.method == "GET":
        
        portfolio = db.execute("SELECT * FROM portfolio WHERE id = :id", id=session["user_id"])
        return render_template("sell.html", portfolio=portfolio)
        
    elif request.method == "POST":
        
        if not request.form.get("symbol"):
            return apology("Please input symbol")
        
        stock=lookup(request.form.get("symbol"))
        if not stock:
            return apology("Symbol does not exist")
        try:    
            sell=int(request.form.get("quantity"))
            if sell<1:
                return apology("Invalid Quantity")
        except:
            return apology("Invalid Quantity")
            
        shares = db.execute("SELECT quantity FROM portfolio WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=stock["symbol"])
        
        if not shares or float(shares[0]["quantity"])<(sell):
            return apology("Not enough shares!")
            
        else:
            
            cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
            db.execute("UPDATE users SET cash = :newcash WHERE id = :id", newcash=cash[0]["cash"]+(float(sell)*(stock["price"])), id=session["user_id"])

            db.execute("INSERT INTO history (id, shares, quantity, total, datetime, buysell) VALUES (:id, :shares, :quantity, :total, :t, :sell)", id=session["user_id"], shares=stock["symbol"], quantity=sell, total=(sell*(stock["price"])), t=(str(datetime.datetime.utcnow())), sell="sell")
            
            oldquantity = db.execute("SELECT quantity FROM portfolio WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=stock["symbol"])
            oldtotal = db.execute("SELECT total FROM portfolio WHERE id = :id AND symbol = :symbol", id=session["user_id"], symbol=stock["symbol"])
            db.execute("UPDATE portfolio SET quantity=:quantity WHERE id = :id AND symbol = :symbol", quantity=float(oldquantity[0]["quantity"])-sell, id=session["user_id"], symbol=stock["symbol"])
            db.execute("UPDATE portfolio SET total=:total WHERE id = :id AND symbol = :symbol", total=float(oldtotal[0]["total"])-(sell*(stock["price"])), id=session["user_id"], symbol=stock["symbol"])
            db.execute("UPDATE portfolio SET lasttransaction=:t WHERE id = :id AND symbol = :symbol", t=(str(datetime.datetime.utcnow())), id=session["user_id"], symbol=stock["symbol"])
        
            shares = db.execute("SELECT quantity FROM portfolio WHERE id = :id", id=session["user_id"])

            if not (shares[0]["quantity"]):
                db.execute("DELETE FROM portfolio WHERE id= :id AND symbol=:symbol", id=session["user_id"], symbol=stock["symbol"])
        
                
    return redirect(url_for("index"))    

@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    if request.method == "GET":
        
        return render_template("password.html")
        
    elif request.method == "POST":
    
        if not request.form.get("password"):
            return apology("Please type a password")
            
        elif request.form.get("password") != request.form.get("passwordagain"):
            return apology("Passwords do not match!")
            
        else:
            db.execute("UPDATE users SET hash = :hash WHERE id = :id", hash=pwd_context.hash(request.form.get("password")), id=session["user_id"])
            
        return render_template("success.html")
        
@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    if request.method == "GET":
        
        return render_template("cash.html")
    
    elif request.method == "POST":
        
        if float(request.form.get("credit"))<0:
            return apology("Please enter a positive amount")
            
        else:
            db.execute("UPDATE users SET cash = cash + :credit where id = :id", credit=float(request.form.get("credit")), id=session["user_id"])
        
        return redirect(url_for("index"))    
            