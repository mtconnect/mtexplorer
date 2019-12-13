
MTExplorer is an UI application to demonstrate the connectivity with MT agents. The info returned from MT agents can be shown in original XML format or translated to HTML with corresponding style sheet. It is designed using Qt (https://www.qt.io/) so it can run in multiple platforms including MacOS, Windows, iPhone and Android devices. 

Here are some screenshots from various platforms:

MacOS

![MacOS](https://user-images.githubusercontent.com/34289248/56448657-e3b6d400-62c5-11e9-8d1b-822a500999dd.png)

Windows

![Windows](https://user-images.githubusercontent.com/34289248/56448645-ad795480-62c5-11e9-89e5-c7b10361eecd.png)

iPhone

![iPhone](https://user-images.githubusercontent.com/34289248/56448745-d4845600-62c6-11e9-97e9-816fe69f9a2b.png)

Android

![Android](https://user-images.githubusercontent.com/34289248/56448831-976c9380-62c7-11e9-8ceb-3ef58cf9b4a7.png)


Building
-------

Download and install qt from [qt](https://www.qt.io/download)

Download and install Xcode for iPhone from [Apple](https://developer.apple.com/xcode/)

Download and install Android SDK for Android devices from [Google](https://developer.android.com/studio)

Open the MTExplorer.pro Qt project file. It should automatically detect the installed platform SDK. Update any configuations if needed. Compile and Run.

For Android and Windows platform, if the MT agents are using https secure protocol, download openssl from [openssl](https://www.openssl.org/source/). For Android platforms, generate openssl shared libraries based on the target Android's device architect and update MTExplorer.pro to include the location of openssl libraries. For Windows, after the build, add the location of libcrypto.dll and libssl.dll to the PATH system variable and restart Qt.

v1.1.0 Release Notes
-------

1. Allow XML text to be selectable.
2. Nicely display XML responses from v1.5 MT Agents

v1.1.1 Release Notes
-------

1. Support displaying json responses from v1.5 MT Agents
2. Reorganize the menu items

Binary Releases v1.1.1
-------

Download [MacOS Installation](https://raw.githubusercontent.com/mtconnect/mtexplorer/v1.1.1/binaries/MacOS/MTExplorer.dmg)

Download [Windows Installation](https://raw.githubusercontent.com/mtconnect/mtexplorer/v1.1.1/binaries/Windows/MTExplorerSetup.zip)
