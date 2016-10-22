<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template  match="/">
<p><strong><xsl:value-of  select="//title"/></strong></p>
<p><xsl:value-of  select="//author"/></p>
</xsl:template>
</xsl:stylesheet>