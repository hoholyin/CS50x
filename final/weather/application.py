from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

import time
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


@app.route("/search", methods=["GET", "POST"])
def search():
    """Get weather information."""
    if request.method == "POST":

        t=(str(datetime.datetime.utcnow()))

        city = request.form.get("city")
        country = request.form.get("country")

        if not country:
            return apology("Please enter a valid location!")

        city = city.replace(" ","+")
        country = country.replace(" ","+")
        google_page_0 = requests.get('https://www.google.com.sg/search?q='+city+'+weather+forecast+'+country+'+weather+worldweatheronline')
        country = country.replace("+"," ")

        soup_0 = BeautifulSoup(google_page_0.text, 'html.parser')

        url_0=url_extractor(soup_0)

        if (url_0[12:30] == 'worldweatheronline'):
            world_weather_page = requests.get(url_0)
        else:
            return apology("Information Unavailable")



        # Create a BeautifulSoup object
        soup = BeautifulSoup(world_weather_page.text, 'html.parser')

        #Getting city name from source
        city_name = soup.find("h1", {"class" : "city_name"}).text
        city_name = city_name[:-71]

        #Getting temp
        world_weather_temp = soup.find("div", {"class" : "report_text temperature"}).text

        #Getting date of query
        today = datetime.date.today()
        date = today.strftime('%d %b %Y')

        # block is a list containing rainfall, sunrise and sunset timings
        block = list(soup.find("div", {"class" : "info_item elem_item"}))
        # rain = block[0].text
        sunrise = block[1].text
        sunrise = sunrise[10:12]+sunrise[13:15]+ " hrs"
        sunset = block[2].text
        sunset = str(int(sunset[10:11])+12)+sunset[12:15]+ " hrs"

        #Extracting chance of rain based on time
        time = soup.find("div", {"class" : "col-md-8 col-sm-7"}).small.strong.text
        hour = str(time)[-8:-1]

        if(hour[0]==' '):
            hour='0'+hour[1:]

        if (hour[-1] == 'p'):
            if int(hour[0:2]) == 12:
                hour_1 = 13
            else:
                hour_1 = int(hour[0:2])+12+1
                while (hour_1>23):
                    hour_1-=24

        else:
            hour_1 = int(hour[0])+1

        if (hour_1 >= 5):
            if (hour_1 <12):
                pop = soup.find("div", {"class" : "tb_row tb_rain"}).div.next_sibling.text
                index_pop = pop_indexer(pop)
                cloud_cover = soup.find("div", {"class" : "tb_row tb_cloud"}).div.next_sibling.text
                index_cc = cloud_indexer(cloud_cover)
            elif (hour_1 <16):
                pop = soup.find("div", {"class" : "tb_row tb_rain"}).div.next_sibling.next_sibling.text
                index_pop = pop_indexer(pop)
                cloud_cover = soup.find("div", {"class" : "tb_row tb_cloud"}).div.next_sibling.next_sibling.text
                index_cc = cloud_indexer(cloud_cover)
            elif (hour_1 <20):
                pop = soup.find("div", {"class" : "tb_row tb_rain"}).div.next_sibling.next_sibling.next_sibling.text
                index_pop = pop_indexer(pop)
                cloud_cover = soup.find("div", {"class" : "tb_row tb_cloud"}).div.next_sibling.next_sibling.next_sibling.text
                index_cc = cloud_indexer(cloud_cover)
            else:
                pop = soup.find("div", {"class" : "tb_row tb_rain"}).div.next_sibling.next_sibling.next_sibling.next_sibling.text
                index_pop = pop_indexer(pop)
                cloud_cover = soup.find("div", {"class" : "tb_row tb_cloud"}).div.next_sibling.next_sibling.next_sibling.next_sibling.text
                index_cc = cloud_indexer(cloud_cover)
        else:
            pop = soup.find("div", {"class" : "tb_row tb_rain"}).div.next_sibling.next_sibling.next_sibling.next_sibling.text
            index_pop = pop_indexer(pop)
            cloud_cover = soup.find("div", {"class" : "tb_row tb_cloud"}).div.next_sibling.next_sibling.next_sibling.next_sibling.text
            index_cc = cloud_indexer(cloud_cover)

        if (hour_1 == 0):
            l_time = '23'+hour[3:5]+' hrs'
        elif (hour_1 < 10):
            l_time = '0'+str(hour_1-1)+hour[3:5]+' hrs'
        else:
            l_time=str(hour_1-1)+hour[3:5]+' hrs'

        try:
            if (int(world_weather_temp.replace(" °c",""))>30):
                index_t = 1
            else:
                index_t = 0
        except:
            if (int(world_weather_temp.replace(" °f",""))>86):
                index_t = 1
            else:
                index_t = 0

        if (index_pop == 0):
            if (index_cc == 0):
                activities = db.execute("SELECT * FROM activities WHERE outdoors = 'Y'")
            elif (index_t == 0):
                activities = db.execute("SELECT * FROM activities WHERE outdoors = 'Y' AND cooling_weather = 'Y'")
            else:
                activities = db.execute("SELECT * FROM activities WHERE outdoors = 'N'")
        else:
            activities = db.execute("SELECT * FROM activities WHERE outdoors = 'N'")


        return render_template("weatherinfo.html", activities=activities, l_time=l_time, pop=pop, city=city_name, country=country, date=date, world_weather_temp=world_weather_temp, sunrise=sunrise, sunset=sunset, cloud_cover=cloud_cover)

    #clicking a link or redirect to come to search
    else:
        countries = db.execute("SELECT * FROM countries")

        return render_template("search.html", countries=countries)

def url_extractor(soup):

    url_0 = soup.find("h3", {"class":"r"} )
    url_1 = url_0.a.get('href')
    url_2, url_3 = url_1.split("=", 1)
    url, url_4 = url_3.split("&", 1)

    return url

def cloud_indexer(cloud):
    if (int(cloud.replace("%",""))>50):
        index_cc = 1
    else:
        index_cc = 0

    return index_cc

def pop_indexer(pop):
    if (int(pop.replace("%",""))>50):
        index_pop = 1
    else:
        index_pop = 0
    return index_pop