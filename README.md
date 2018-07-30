# WebXR: A board game using Augmented Reality
This board game is implemented on the top of webxr-polyfill framework. NodeJS is used as the server-side framework. webxr-polyfill framework with examples can be downloaded from https://github.com/mozilla/webxr-polyfill
This game is already hosted on  https://webxr-game.herokuapp.com

## WARNING
The game is developed on unstable version of webxr-polyfill. for more information please go through the readme of webxr-polyfill from from https://github.com/mozilla/webxr-polyfill


## Building and Running the examples
Clone the master branch of this repo from https://gitlab.tubit.tu-berlin.de/shaondebnath/webxrgame

	npm install   # downloads webpack and an http server
	npm start     # builds the polyfill in dist/webxr-polyfill.js and start the http server in the current directory

Using one of the supported browsers listed below, go to http://YOUR_HOST_NAME:8080/

## Supported Devices and browsers

###iOS users
Install XR Browser from Apple Store(iOS 11.0 or later)
https://itunes.apple.com/us/app/webxr-viewer/id1295998056?mt=8 


###Android Users:
Step1: Install Tango Core (https://github.com/google-ar/arcore-android-sdk/releases/download/sdk-preview/arcore-preview.apk) (also can be found in google play store)

Step2: Install Browser: WebARonARCore (https://github.com/google-ar/WebARonARCore/raw/webarcore_57.0.2987.5/apk/WebARonARCore.apk)

###Supported device list
Supported devices list can be found at https://developers.google.com/ar/discover/supported-devices 
