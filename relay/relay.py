import json
from flask import Flask, request
import requests 

app = Flask(__name__)

#Add Url here
url = ""

@app.route('/', methods=['POST'])
def index():
    print(request.get_json())
    response = requests.post(url, json=request.get_json())
    return response.text

app.run(host='0.0.0.0', port=5000)  