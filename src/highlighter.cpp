#include "highlighter.h"
#include <QPalette>

Highlighter::Highlighter(QTextDocument* parent) : QSyntaxHighlighter(parent){

    qClassFormat.setFontWeight(QFont::Bold);
    qClassFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
    rule.format = qClassFormat;
    highlightingRules.append(rule);

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Z][a-z]+\\b"));
    rule.format = classFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString& text){
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

HighlighterCPP::HighlighterCPP(QTextDocument* parent) : Highlighter(parent)
{

    keywordFormat.setForeground(Qt::darkCyan);
    keywordFormat.setFontWeight(QFont::Bold);
    const QList<QString> keywordPatterns = {
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bclass\\b"), QStringLiteral("\\bconst\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bprivate\\b"), QStringLiteral("\\bprotected\\b"), QStringLiteral("\\bpublic\\b"),
        QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsignals\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bslots\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\bbool\\b")
        // What the fuck bro
    };

    for (const auto& pattern : keywordPatterns){
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
}

HighlighterPython::HighlighterPython(QTextDocument* parent) : Highlighter(parent)
{

    keywordFormat.setForeground(Qt::darkCyan);
    keywordFormat.setFontWeight(QFont::Bold);
    const QList<QString> keywordPatterns = {

        QStringLiteral("\\bFalse\\b"), QStringLiteral("\\bawait\\b"), QStringLiteral("\\belse\\b"),
        QStringLiteral("\\bimport\\b"), QStringLiteral("\\bpass\\b"), QStringLiteral("\\bNone\\b"),
        QStringLiteral("\\bbreak\\b"), QStringLiteral("\\bexcept\\b"), QStringLiteral("\\bfinally\\b"),
        QStringLiteral("\\bin\\b"), QStringLiteral("\\braise\\b"), QStringLiteral("\\bTrue\\b"),
        QStringLiteral("\\bclass\\b"), QStringLiteral("\\bis\\b"), QStringLiteral("\\breturn\\b"),
        QStringLiteral("\\band\\b"), QStringLiteral("\\bcontinue\\b"), QStringLiteral("\\bfor\\b"),
        QStringLiteral("\\blambda\\b"), QStringLiteral("\\btry\\b"), QStringLiteral("\\bas\\b"),
        QStringLiteral("\\bdef\\b"), QStringLiteral("\\bfrom\\b"), QStringLiteral("\\bnonlocal\\b"),
        QStringLiteral("\\bwhile\\b"), QStringLiteral("\\bassert\\b"), QStringLiteral("\\bdel\\b"),
        QStringLiteral("\\bglobal\\b"), QStringLiteral("\\bnot\\b"), QStringLiteral("\\bwith\\b"),
        QStringLiteral("\\basync\\b"), QStringLiteral("\\belif\\b"), QStringLiteral("\\bif\\b"),
        QStringLiteral("\\bor\\b"), QStringLiteral("\\byield\\b"),

    };

    for (const auto& pattern : keywordPatterns){
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
}
