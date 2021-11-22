MTExplorer is now under further development with [Metalogi LLC](https://www.metalogi.io). It is now called Metalogi MetaStudio. A [FREE new release](https://www.metalogi.io/download) is now available with many new improvements. Combined with Metalogi MetaAgent, you can manage and reconfigure your MTConnect Agents and immediately provide MTConnect, OPC UA and NC-Link interfaces to your applications. Give it a try and we love to hear from you and further contribute to our MTConnect Community.
----

![MetaStudio-Mac-2](https://user-images.githubusercontent.com/34289248/142936784-dfbeb8e5-64c8-46bd-9b4d-36b6914a34ef.png)
----





MTExplorer is an UI application to demonstrate the connectivity with MT agents. The info returned from MT agents can be shown in original XML format or translated to HTML with corresponding style sheet. It is designed using Qt (https://www.qt.io/) so it can run in multiple platforms including MacOS, Windows, iPhone and Android devices. 

Here are some screenshots from various platforms:

MacOS

![MacOS](https://user-images.githubusercontent.com/34289248/75584988-eaee5880-5a25-11ea-9d91-5f4a5f5a4edf.png)

Windows

![Windows](https://user-images.githubusercontent.com/34289248/75585891-fe9abe80-5a27-11ea-9764-0abb6eea52ff.png)

iPhone

![iPhone](https://user-images.githubusercontent.com/34289248/75585292-90a1c780-5a26-11ea-8348-c1f42289cd27.png)

Android

![Android](https://user-images.githubusercontent.com/34289248/75588239-145eb280-5a2d-11ea-8f61-41fc9106a128.png)



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

v1.1.2 Release Notes
-------

1. Move prebuilt binary packages to release tab
2. Color alternating rows to improve the readability of tables. 
3. Use different column attributes and colors for Samples/Events/Conditions tables.

Pre-built Binary Releases
-------

Windows and MacOS pre-built binaries are available in the release tab:

https://github.com/mtconnect/mtexplorer/releases

