import json
from flask import Flask, request
import requests 

app = Flask(__name__)

url = "https://prod-99.westeurope.logic.azure.com:443/workflows/12f484e2182142a3809dbf8283d2aa28/triggers/manual/paths/invoke?api-version=2016-06-01&sp=%2Ftriggers%2Fmanual%2Frun&sv=1.0&sig=5eoc065JdR6Cr0J32dKOWdZCEtBIpCqKKAxNl77wQDs"

@app.route('/', methods=['POST'])
def index():
    print(request.get_json())
    response = requests.post(url, json=request.get_json())
    return response.text

app.run(host='0.0.0.0', port=5000)  