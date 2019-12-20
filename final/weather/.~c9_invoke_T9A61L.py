from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

import datetime
import requests
from bs4 import BeautifulSoup

# configure application
app = Flask(__name__)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///weather.db")

@app.route("/")
def index():
    
    return render_template("index.html")

def apology(message, code=400):
    """Renders message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


# TO EDIT to search by flight number
@app.route("/search", methods=["GET", "POST"])
def search():
    """Get weather information."""
    if request.method == "POST":
        
        t=(str(datetime.datetime.utcnow()))
        
        location = request.form.get("location")
        # location = 'bedok'
        
        if not location:
            return apology("Please enter a valid location!")
        results = db.execute("SELECT dt, maxtemp, mintemp, avgtemp, rainfall, sunrise, sunset FROM weather WHERE dt_query = :dt_query", dt_query=t")
        location = location.replace(" ","+")
        google_page = requests.get('https://www.google.com.sg/search?q='+location+'-weather+singapore+worldweatheronline')

        soup_0 = BeautifulSoup(google_page.text, 'html.parser')

        url_0 = soup_0.find("h3", {"class":"r"} )
        url_1 = url_0.a.get('href')
        url_2, url_3 = url_1.split("=", 1)
        url, url_4 = url_3.split("&", 1)

        world_weather_page = requests.get(url)

        # Create a BeautifulSoup object
        soup = BeautifulSoup(world_weather_page.text, 'html.parser')
        
        city_name_0 = soup.find("h1", {"class": "city_name"}).text
        city_name = city_name_0[0:-17]

        world_weather_temp_max = soup.find("div", {"class" : "max_temp"}).text
        max_temp = int(world_weather_temp_max[4] + world_weather_temp_max[5])

        world_weather_temp_min = soup.find("div", {"class" : "min_temp"}).text
        min_temp = int(world_weather_temp_min[5] + world_weather_temp_min[6])

        avg_temp = round((max_temp + min_temp)/2, 1)

        date0 = soup.find("div", {"class" : "result_local result_item"}).text
        date = date0[14:]

        # block is a list containing rainfall, sunrise and sunset timings
        block = list(soup.find("div", {"class" : "info_item elem_item"}))
        # rain = block[0].text
        sunrise = block[1].text
        sunset = block[2].text

        condition = soup.find("div", {"class" : "info_item light_text"}).text
        
        pop = soup.find("div", {"class" : "report_text"}).text
        
        
        #db.execute("INSERT INTO weather (location, max_temp, min_temp, avg_temp, date, rain, sunrise, sunset, condition, dt_query) VALUES (:location, :max_temp, :min_temp, :avg_temp, :date, :rain, :sunrise, :sunset, :condition, :dt_query)", location=location, max_temp=max_temp, avg_temp=avg_temp, date=date, rain=rain, sunrise=sunrise, sunset=sunset, condition=condition)

        #results = db.execute("SELECT * FROM weather WHERE dt_query = :dt_query", dt_query=t)
    
        return render_template("weatherinfo.html", location=city_name, date=date, max_temp=max_temp, min_temp=min_temp, avg_temp=avg_temp, rain=pop, sunrise=sunrise, sunset=sunset)
        
    #clicking a link or redirect to come to search
    else:
        return render_template("search.html")