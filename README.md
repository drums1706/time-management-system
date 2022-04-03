# Time Management System

A short description about the project and/or client.

## Getting Started

### Prerequisites

* Ubuntu 20.04.4 LTS
  * Python 3 installed
  * Python3-pip installed
  * Screen installed

### Installation

1. Import project
```
https://github.com/drums1706/time-management-system.git
```
2. Change the Wi-Fi password and username in `mbed_app.json`.
![Image of the file](./assets/wifi_config.png)

3. Compile the cpp files and upload them to your IoTkit.

### Python relay deployment

1. Connect to the linux machine / server.

2. Import the project.
```
https://github.com/drums1706/time-management-system.git
```

3. Open the `relay` folder.

4. Install the dependencies:
```
pip3 install flask requests
```

5. Run the relay script:

Option A: Run it as long as your terminal is open:
```
python3 relay.py
```

Option B: Run it in the background, without the terminal being open all the time:
```
screen -dmS python-relay python3 relay.py
```
This will start a separate session with the name `python-relay`.
* To interact with the session, use `screen -r python-relay`
* To exit from the sesison, use `CTRL` + `A` + `D` or `CTRL` + `C` to exit and kill


### Power Apps / Automate

## Documentation

### Reflection

The project was very interessting and we learned alot from this modul. We learned what an iotkit is an what its able to do. The most interessting and challenging part of the whole project was, that we had to do a Https post request to a server. But the most fun part to do was to implement the RFID reader. Many challenges stood before us, but we managed to conqueror them.

### Use HTTPS

We wanted to make a Https POST request to our Azure server but quickly realized, that this wasn't possible, because the version of the request wasn't supported. So we had to think of another way to make the request. We later came up with an idea to make a relay to the Azure database. We used Python 3 and the package called flask to accept http requests and forward them as https to Azure, by using the package called requests.

### Cloud

We used Azure to store and visualize our data. But to host the python relay, we used a server (own cloud) from our friend Dillan.

### Knowledgebase

...
