<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/solar">
		<table width="60%" align="center" border="1" cellpadding="2">
			<tr align="center" bgcolor="#CCCCCC">
				<td>№</td>
				<td>Название</td>
				<td>Расстояние от Солнца (а.е.)</td>
				<td>Период обращения (г.)</td>
				<td>Период вращения вокруг своей оси (ч.)</td>
				<td>Масса относительно Земли</td>
				<td>Диаметр (км.)</td>
				<td>Количество спутников</td>
			</tr>
			<xsl:for-each select="planet">
			<xsl:sort order="ascending" select="satellite_number" data-type="number"/>
			<xsl order="ascending" select="@caption" data-type="text"/>
				<tr align="center">
					<xsl:if test="diametr &lt;10000">
						<xsl:attribute name="bgcolor">gray</xsl:attribute>
					</xsl:if>
					<td><xsl:value-of select="position()"/></td>
					<td><xsl:value-of select="@caption"/></td>
					<td><xsl:value-of select="distance"/></td>
					<td><xsl:value-of select="circulation_period"/></td>
					<td><xsl:value-of select="revolution_period"/></td>
					<td><xsl:value-of select="weight"/></td>
					<td><xsl:value-of select="diametr"/></td>
					<td><xsl:value-of select="satellite_number"/></td>
				</tr>
			</xsl:for-each>
		</table>
	</xsl:template>
</xsl:stylesheet>

<!--
xsl:template - Задает шаблон преобразования для выходного потока.
xsl:value-of - Создает текстовый узел и вставляет некоторое значение в дерево-результат.
xsl:for-each - Позволяет создать цикл из нескольких узлов в выходном потоке.
xsl:sort - Позволяет создать сортировку набора узлов. Элемент <xsl:sort> всегда является дочерним элементом элемента <xsl:for-each>.
xsl:if - Позволяет писать условные выражения. Несет шаблон, который будет выполняться при определенном условии.
-->