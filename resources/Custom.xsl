<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" xmlns:m="urn:mtconnect.org:MTConnectStreams:1.3" >
    <xsl:output method="html" encoding="UTF-8" indent="yes"/>
    <xsl:template match="/">
        <head>
        <style>
        body {font-family: Arial;}

        #navbar {
          background-color: #f1f1f1;
          position: fixed; /* Make it stick/fixed */
          top: 0; /* Stay on top */
          width: 100%; /* Full width */
          transition: top 0.3s; /* Transition effect when sliding down (and up) */
        }

        /* Style the tab */
        .tab {
          overflow: hidden;
          border: 1px solid #ccc;
        }

        /* Style the buttons inside the tab */
        .tab button {
          background-color: inherit;
          float: left;
          border: none;
          outline: none;
          cursor: pointer;
          padding: 14px 16px;
          transition: 0.3s;
          font-size: 17px;
        }

        /* Change background color of buttons on hover */
        .tab button:hover {
          background-color: #ddd;
        }

        /* Create an active/current tablink class */
        .tab button.active {
          background-color: #ccc;
        }

        /* Style the tab content */
        .tabcontent {
          display: none;
          padding: 6px 12px;
          border: 1px solid #ccc;
          border-top: none;
        }
        </style>
        </head>

        <body>
        <script type="text/javascript" src="qrc:/resources/Custom.js">//</script>

        <div class="tab" id="navbar" >
          <button class="tablinks" onclick="openCity(event, 'London')">London</button>
          <button class="tablinks" onclick="openCity(event, 'Paris')">Paris</button>
          <button class="tablinks" onclick="openCity(event, 'Tokyo')">Tokyo</button>
        </div>

        <div id="London" class="tabcontent">
          <h3>London</h3>
          <p>London is the capital city of England.</p>
        </div>

        <div id="Paris" class="tabcontent">
          <h3>Paris</h3>
          <p>Paris is the capital of France.</p>
        </div>

        <div id="Tokyo" class="tabcontent">
          <h3>Tokyo</h3>
          <p>Tokyo is the capital of Japan.</p>
        </div>


            <xsl:apply-templates select="/*[local-name()='MTConnectStreams']/*[local-name()='Streams']/*[local-name()='DeviceStream']" />

        </body>
    </xsl:template>

    <xsl:template match="*[local-name()='DeviceStream']">
        <h2>Device: <xsl:value-of select="@name"/>
        <xsl:text>; UUID: </xsl:text><xsl:value-of select="@uuid"/>
        </h2>
        <xsl:apply-templates select="*[local-name()='ComponentStream']"/>
    </xsl:template>

    <xsl:template match="*[local-name()='Header']">
    </xsl:template>

    <xsl:template match="*[local-name()='ComponentStream']">
        <h3>
            <xsl:value-of select="@component" />
            <xsl:text> : </xsl:text>
            <xsl:value-of select="@name" />
        </h3>
        <xsl:apply-templates select="	*[local-name()='Samples']"/>
        <xsl:apply-templates select="	*[local-name()='Events']"/>
        <xsl:apply-templates select="	*[local-name()='Condition']"/>
        <br> </br>
    </xsl:template>

    <xsl:template match="*">
        <p><xsl:value-of select="name()"/></p>
        <table border="1" cellpadding="4" class="data-item">
            <thead>
                <tr><th>Timestamp</th><th>Type</th><th>Sub Type</th><th>Name</th><th>Id</th><th>Sequence</th><th>Value</th></tr>
            </thead>
            <tbody>
                <xsl:for-each select="*">
                    <tr>
                        <td><xsl:value-of select="substring-before(@timestamp,'T')"/>
                            <xsl:text> </xsl:text>
                            <xsl:value-of select="substring-before(substring-after(@timestamp,'T'),'.')"/>
                        </td>
                        <td><xsl:value-of select="name()"/></td>
                        <td><xsl:value-of select="@subType"/></td>
                        <td><xsl:value-of select="@name"/></td>
                        <td><xsl:value-of select="@dataItemId"/></td>
                        <td><xsl:value-of select="@sequence"/></td>
                        <td><xsl:value-of select="."/></td>
                    </tr>
                </xsl:for-each>
            </tbody>
        </table>
    </xsl:template>
</xsl:stylesheet>
