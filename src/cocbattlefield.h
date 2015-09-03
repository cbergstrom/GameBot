#ifndef COCBATTLEFIELD_H
#define COCBATTLEFIELD_H

#include <QObject>
#include <QPoint>
#include <QString>
#include <QRect>
#include <QFile>
#include <QDataStream>

#include <opencv2/imgproc/imgproc.hpp>

#include "resourcemanager.h"

// Program logic. Only basic Qt types allowed (TODO)

class Match {
public:
    const QPoint pos;
    const float value; // if methods other than TM_CCORR_NORMED are ever used, value should be normalized to reflect accuracy and not raw match
    Match(const int x, const int y, const float value)
        : pos(x, y), value(value)
    {}
    Match(const Match &m)
        : pos(m.pos),
          value(m.value)
    {}
};

class FeatureMatch {
public:
    const Feature *ftr;
    const Sprite *sprite;
    const Match match;
    FeatureMatch(const Feature *ftr, const Sprite *sprite, const Match &match)
        : ftr(ftr),
          sprite(sprite),
          match(match)
    {}
};

class BattlefieldSignals : public QObject
{
    Q_OBJECT
public:
    explicit BattlefieldSignals(QObject *parent = 0);
signals:
    void debugChanged(const QString &filename);
};

class Grid { // grid info in the default screenshot projection (rot45, known x/y ratio)
public:
    const float horzDist = 42; // horizontal pixel distance between 2 consecutive grid lines (empirical)
    const float vertDist = 31.5; // vertical (for slope)
    // const int size = 0; // number of tiles from origin (currently not needed, therefore infinite)
    const QPoint origin; // offset
    Grid(const QPoint &origin)
        : origin(origin)
    {}
};

class CocBattlefield
{
    const cv::Mat screen;
    ResourceManager *buildings;
    BattlefieldSignals *sig;
    Grid *grid = NULL;
public:
    CocBattlefield(const QString &filepath, ResourceManager *buildings, BattlefieldSignals *proxy=NULL);
    const std::list<FeatureMatch> analyze();
    ~CocBattlefield();
public:
    inline double getScale() {
        return buildings->getScale();
    }
protected:
    double find_scale();
    void find_grid();
    void draw_grid();
};

#endif // COCBATTLEFIELD_H
