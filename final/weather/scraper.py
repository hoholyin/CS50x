import requests
from bs4 import BeautifulSoup

def scraper(location)

    location = location.replace(" ","+")
    google_page = requests.get('https://www.google.com.sg/search?q='+location+'-weather+singapore+worldweatheronline')

    soup_0 = BeautifulSoup(google_page.text, 'html.parser')

    url_0 = soup_0.find("h3", {"class":"r"} )
    url_1 = url_0.a.get('href')
    url_2, url_3 = url_1.split("=", 1)
    url, url_4 = url_3.split("&", 1)

    print("Getting query from " + url + "...")
    world_weather_page = requests.get(url)

    # Create a BeautifulSoup object
    soup = BeautifulSoup(world_weather_page.text, 'html.parser')


    world_weather_temp_max = soup.find("div", {"class" : "max_temp"}).text
    max_temp = int(world_weather_temp_max[4] + world_weather_temp_max[5])

    world_weather_temp_min = soup.find("div", {"class" : "min_temp"}).text
    min_temp = int(world_weather_temp_min[5] + world_weather_temp_min[6])

    avg_temp = round((max_temp + min_temp)/2, 1)

    day = soup.find("div", {"class" : "info_item img_wrap col-sm-12 col-xs-3 wh_prime_item_1"}).text

# block is a list containing rainfall, sunrise and sunset timings
    block = list(soup.find("div", {"class" : "info_item elem_item"}))
    rain = block[0].text
    sunrise = block[1].text
    sunset = block[2].text

    condition = soup.find("div", {"class" : "info_item light_text"}).text
