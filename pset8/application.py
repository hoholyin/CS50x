import os
import re
import string

from flask import Flask, jsonify, render_template, request

from cs50 import SQL
from helpers import lookup

# Configure application
app = Flask(__name__)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///mashup.db")


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Render map"""
    if not os.environ.get("API_KEY"):
        raise RuntimeError("API_KEY not set")
    return render_template("index.html", key=os.environ.get("API_KEY"))


@app.route("/articles")
def articles():
    """Look up articles for geo"""
    geo = request.args.get("geo")
    if not geo:
        raise RuntimeError("Location not set")
    
    article = lookup(geo)
    
    if len(article)>5:
        return jsonify([article[0], article[1], article[2], article[3], article[4]])
    else:
        return jsonify([article])


@app.route("/search")
def search():
    """Search for places that match query"""

    # '%' is SQL's wildcard
    q0 = request.args.get("q")
    q1 = q0 + "%"
    #this is done to calculate the number of words in the query
    
    #check if it's an incomplete query and return results of autocomplete query
    results = db.execute("SELECT * from places where postal_code = :q OR place_name = :q OR admin_name1 = :q OR admin_code1 = :q", q=q0)
    #if theres no results from autocomplete
    if not results:
        results = db.execute("SELECT * from places where postal_code LIKE :q OR place_name LIKE :q OR admin_name1 LIKE :q OR admin_code1 LIKE :q", q=q1)
        if not results:
            # remove commas in input if there are
            qnow = q0.replace(",","")
            qnow = qnow.replace(";","")
            #split query into each word (they will automatically split at the spaces)
            data = qnow.split()

            for i in range (len(data)):
            #remove last word by using splittosearch function
                qnow=splittosearch(qnow)
                results = db.execute("SELECT * from places where postal_code LIKE :q OR place_name LIKE :q OR admin_name1 LIKE :q OR admin_code1 LIKE :q", q=qnow)
            #if removing the last word gives a result, break out of loop and return results
            #if not, continue to remove next last word until i reaches len(data) (number of words in query)
                if len(results)>0:
                    break

            
    if len(results)>5:
        return jsonify(results[0], results[1], results[2], results[3], results[4])
    else:
        return jsonify(results)


@app.route("/update")
def update():
    """Find up to 10 places within view"""

    # Ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")

    # Ensure parameters are in lat,lng format
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")

    # Explode southwest corner into two variables
    sw_lat, sw_lng = map(float, request.args.get("sw").split(","))

    # Explode northeast corner into two variables
    ne_lat, ne_lng = map(float, request.args.get("ne").split(","))

    # Find 10 cities within view, pseudorandomly chosen if more within view
    if sw_lng <= ne_lng:

        # Doesn't cross the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude AND longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    else:

        # Crosses the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude OR longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    # Output places as JSON
    return jsonify(rows)

def splittosearch(q):
    data = q.split()
    q_first=""
    for i in range(len(data)-1):
        if (i<len(data)-2):
            q_first=q_first+data[i]+" "
        else:
            q_first=q_first+data[i]
    return q_first
    