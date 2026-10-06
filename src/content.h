#pragma once

#include <QColor>
#include <QString>
#include <QVector>

struct ElementInfo {
    QString name;
    QString nature;
    QString organ;
    QString fu;
    QString sense;
    QString tissue;
    QString season;
    QString emotion;
    QString flavor;
    QString colorName;
    QColor color;
    QString trigram;
    QString generates;
    QString restrains;
    QString care;
};

struct TrigramInfo {
    QString name;
    QString symbol;
    QString nature;
    QString body;
    QString organHint;
    QString meaning;
};

struct SeasonInfo {
    QString name;
    QString element;
    QString yijing;
    QString tcm;
};

const QVector<ElementInfo> &elementCatalog();
const QVector<TrigramInfo> &trigramCatalog();
const QVector<SeasonInfo> &seasonCatalog();
QString homeIntroHtml();
QString disclaimerHtml();
