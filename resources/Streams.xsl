<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions" xmlns:m="urn:mtconnect.org:MTConnectStreams:1.3" >
        <xsl:output method="html" encoding="UTF-8" indent="yes"/>
        <xsl:template match="/">
                <body>
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

        <xsl:template match="*[local-name()='Condition']">
                <p><xsl:value-of select="name()"/></p>
                <table border="1" cellpadding="4" class="data-item">
                        <thead>
                                <tr><th>Timestamp</th><th>Key</th><th>Name</th><th>Type</th><th>Sub Type</th><th>Native Code</th><th>Id</th><th>Sequence</th><th>Value</th></tr>
                        </thead>
                        <tbody>
                                <xsl:for-each select="*">
                                    <xsl:variable name="altColor">
                                        <xsl:choose>
                                            <xsl:when test="position() mod 2 = 0">#FFFFFF</xsl:when>
                                            <xsl:otherwise>#FF6F33</xsl:otherwise>
                                        </xsl:choose>
                                    </xsl:variable>
                                    <tr bgcolor="{$altColor}">
                                        <td><xsl:value-of select="substring-before(@timestamp,'T')"/>
                                            <xsl:text> </xsl:text>
                                            <xsl:value-of select="substring-before(substring-after(@timestamp,'T'),'.')"/>
                                        </td>
                                        <td><xsl:value-of select="name()"/></td>
                                        <td><xsl:value-of select="@name"/></td>
                                        <td><xsl:value-of select="@type"/></td>
                                        <td><xsl:value-of select="@subType"/></td>
                                        <td><xsl:value-of select="@nativeCode"/></td>
                                        <td><xsl:value-of select="@dataItemId"/></td>
                                        <td><xsl:value-of select="@sequence"/></td>
                                        <td><xsl:value-of select="."/></td>
                                    </tr>
                                </xsl:for-each>
                        </tbody>
                </table>
        </xsl:template>


        <xsl:template match="*[local-name()='Events']">
                <p><xsl:value-of select="name()"/></p>
                <table border="1" cellpadding="4" class="data-item">
                        <thead>
                                <tr><th>Timestamp</th><th>Key</th><th>Name</th><th>Sub Type</th><th>Comp Id</th><th>Id</th><th>Sequence</th><th>Value</th></tr>
                        </thead>
                        <tbody>
                                <xsl:for-each select="*">
                                    <xsl:variable name="altColor">
                                        <xsl:choose>
                                            <xsl:when test="position() mod 2 = 0">#FFFFFF</xsl:when>
                                            <xsl:otherwise>#DFE45B</xsl:otherwise>
                                        </xsl:choose>
                                    </xsl:variable>
                                    <tr bgcolor="{$altColor}">
                                        <td><xsl:value-of select="substring-before(@timestamp,'T')"/>
                                            <xsl:text> </xsl:text>
                                            <xsl:value-of select="substring-before(substring-after(@timestamp,'T'),'.')"/>
                                        </td>
                                        <td><xsl:value-of select="name()"/></td>
                                        <td><xsl:value-of select="@name"/></td>
                                        <td><xsl:value-of select="@subType"/></td>
                                        <td><xsl:value-of select="@compositionId"/></td>
                                        <td><xsl:value-of select="@dataItemId"/></td>
                                        <td><xsl:value-of select="@sequence"/></td>
                                        <td><xsl:value-of select="."/></td>
                                    </tr>
                                </xsl:for-each>
                        </tbody>
                </table>
        </xsl:template>

        <xsl:template match="*[local-name()='Samples']">
                <p><xsl:value-of select="name()"/></p>
                <table border="1" cellpadding="4" class="data-item">
                        <thead>
                                <tr><th>Timestamp</th><th>Key</th><th>Name</th><th>Type</th><th>Sub Type</th><th>Comp Id</th><th>Id</th><th>Sequence</th><th>Value</th></tr>
                        </thead>
                        <tbody>
                                <xsl:for-each select="*">
                                    <xsl:variable name="altColor">
                                        <xsl:choose>
                                            <xsl:when test="position() mod 2 = 0">#FFFFFF</xsl:when>
                                            <xsl:otherwise>#D3DFEE</xsl:otherwise>
                                        </xsl:choose>
                                    </xsl:variable>
                                    <tr bgcolor="{$altColor}">
                                        <td><xsl:value-of select="substring-before(@timestamp,'T')"/>
                                            <xsl:text> </xsl:text>
                                            <xsl:value-of select="substring-before(substring-after(@timestamp,'T'),'.')"/>
                                        </td>
                                        <td><xsl:value-of select="name()"/></td>
                                        <td><xsl:value-of select="@name"/></td>
                                        <td><xsl:value-of select="@type"/></td>
                                        <td><xsl:value-of select="@subType"/></td>
                                        <td><xsl:value-of select="@compositionId"/></td>
                                        <td><xsl:value-of select="@dataItemId"/></td>
                                        <td><xsl:value-of select="@sequence"/></td>
                                        <td><xsl:value-of select="."/></td>
                                    </tr>
                                </xsl:for-each>
                        </tbody>
                </table>
        </xsl:template>
</xsl:stylesheet>
