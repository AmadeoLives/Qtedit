#pragma once
#include <QSyntaxHighlighter>
#include <QRegularExpression>

class Highlighter : public QSyntaxHighlighter {
Q_OBJECT

public:
    Highlighter(QTextDocument* parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

public:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    HighlightingRule rule;
    QList<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpr;
    QRegularExpression commentEndExpr;

    QTextCharFormat keywordFormat;
    QTextCharFormat qClassFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

class HighlighterCPP : public Highlighter {
Q_OBJECT
public:
    HighlighterCPP(QTextDocument* parent = nullptr);
};

class HighlighterPython : public Highlighter {
Q_OBJECT
public:
    HighlighterPython(QTextDocument* parent = nullptr);
};
