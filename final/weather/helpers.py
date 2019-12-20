# import libraries
import csv
import requests
import datetime


from flask import redirect, render_template, request, session
from functools import wraps
from bs4 import BeautifulSoup
from cs50 import SQL


db = SQL("sqlite:///flights.db")

def lookup(location):
    """Look up search for location."""
    
    # reject location if it starts with caret
    if location.startswith("^"):
        return None

    # reject location if it contains comma
    if "," in location:
        return None
    
    t=(str(datetime.datetime.utcnow()))
    # Collect first page of artists’ list
    page = requests.get('https://www.google.com.sg/search?q='+location+'+singapore+worldweatheronline)
    # Create a BeautifulSoup object
    soup = BeautifulSoup(page.text, 'html.parser')
    # Pull all text from the BodyText div
    weather = soup.find(class_='info_item light_text')
    # Pull text from all instances of <a> tag within BodyText div
    temp = weather.h2.text
    db.execute("INSERT INTO flights (AIRLINE, DT_OF_QUERY) VALUES (:AIRLINE, :DT_OF_QUERY)", AIRLINE=temp, DT_OF_QUERY=t)
