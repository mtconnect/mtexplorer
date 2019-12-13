#include "xmlsyntaxhighlighter.h"

XmlSyntaxHighlighter::XmlSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // tag format
    tagFormat.setForeground(QColor(66, 122, 244, 255)); // blue
    tagFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("(<[a-zA-Z:]+\\b|<\\?[a-zA-Z:]+\\b|\\?>|>|/>|</[a-zA-Z:]+>)");
    rule.format = tagFormat;
    highlightingRules.append(rule);

    // attribute format
    attributeFormat.setForeground(QColor(58, 183, 139, 255)); // green
    rule.pattern = QRegExp("[a-zA-Z:]+=");
    rule.format = attributeFormat;
    highlightingRules.append(rule);

    // attribute content format
    attributeContentFormat.setForeground(QColor(214, 155, 66, 255)); // orange
    rule.pattern = QRegExp("(\"[^\"]*\"|'[^']*')");
    rule.format = attributeContentFormat;
    highlightingRules.append(rule);

    // jsonContentFormat format
    jsonKeyFormat.setForeground(QColor(58, 183, 139, 255)); // green
    rule.pattern = QRegExp("\"[a-zA-Z:]+\":");
    rule.format = jsonKeyFormat;
    highlightingRules.append(rule);

    jsonAttributeFormat.setForeground(QColor(66, 122, 244, 255)); // blue
    jsonAttributeFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("(\"[a-zA-Z:]+\": *\\[)|(\"[a-zA-Z:]+\": *\\{)");
    rule.format = jsonAttributeFormat;
    highlightingRules.append(rule);


    commentFormat.setForeground(Qt::lightGray);
    commentFormat.setFontItalic(true);

    commentStartExpression = QRegExp("<!--");
    commentEndExpression = QRegExp("-->");
}

void XmlSyntaxHighlighter::highlightBlock(const QString &text)
{
     foreach (const HighlightingRule &rule, highlightingRules) {
         QRegExp expression(rule.pattern);
         int index = text.indexOf(expression);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = text.indexOf(expression, index + length);
         }
     }
     setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = text.indexOf(commentStartExpression);

     while (startIndex >= 0) {
         int endIndex = text.indexOf(commentEndExpression, startIndex);
         int commentLength;
         if (endIndex == -1) {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         } else {
             commentLength = endIndex - startIndex
                             + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, commentFormat);
         startIndex = text.indexOf(commentStartExpression,
                                                 startIndex + commentLength);
     }
}
