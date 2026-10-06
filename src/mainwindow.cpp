#include "mainwindow.h"
#include "content.h"
#include "fivephasewidget.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QTextBrowser>
#include <QVBoxLayout>

namespace {

QTextBrowser *makeBrowser(const QString &html = {})
{
    auto *view = new QTextBrowser;
    view->setOpenExternalLinks(false);
    view->setFrameShape(QFrame::NoFrame);
    view->setHtml(html);
    return view;
}

QWidget *wrap(QWidget *inner)
{
    auto *page = new QWidget;
    auto *layout = new QVBoxLayout(page);
    layout->setContentsMargins(20, 16, 20, 16);
    layout->addWidget(inner);
    return page;
}

} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("易医科普 — 周易与中医"));
    resize(960, 640);
    setMinimumSize(820, 540);

    setStyleSheet(QStringLiteral(R"(
        QMainWindow, QWidget#central { background: #121620; color: #e6ebf5; }
        QListWidget {
            background: #1a2130;
            border: none;
            color: #c5d0e0;
            font-size: 15px;
            padding: 8px 0;
            outline: none;
        }
        QListWidget::item { padding: 12px 18px; }
        QListWidget::item:selected { background: #3d6dff; color: white; }
        QTextBrowser {
            background: transparent;
            color: #d7deea;
            font-size: 15px;
            line-height: 1.5;
        }
        QLabel[role="title"] { color: #e6ebf5; font-size: 22px; font-weight: 600; }
        QPushButton {
            background: #2a3244;
            color: #e6ebf5;
            border: none;
            border-radius: 8px;
            padding: 8px 12px;
            font-size: 14px;
        }
        QPushButton:hover { background: #3a445c; }
        QPushButton[selected="true"] { background: #3d6dff; }
        QLabel#disclaimer {
            color: #9aa8bd;
            font-size: 12px;
            padding: 6px 12px;
        }
    )"));

    auto *central = new QWidget;
    central->setObjectName(QStringLiteral("central"));
    setCentralWidget(central);
    auto *root = new QHBoxLayout(central);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    m_nav = new QListWidget;
    m_nav->setFixedWidth(168);
    m_nav->addItems({
        QStringLiteral("总览"),
        QStringLiteral("阴阳五行"),
        QStringLiteral("八卦取象"),
        QStringLiteral("四季养生"),
        QStringLiteral("阅读说明"),
    });
    m_nav->setCurrentRow(0);

    m_stack = new QStackedWidget;

    m_stack->addWidget(wrap(makeBrowser(homeIntroHtml())));

    auto *phasePage = new QWidget;
    auto *phaseLayout = new QHBoxLayout(phasePage);
    m_phases = new FivePhaseWidget;
    m_elementDetail = makeBrowser();
    phaseLayout->addWidget(m_phases, 1);
    phaseLayout->addWidget(m_elementDetail, 1);
    m_stack->addWidget(phasePage);

    auto *trigramPage = new QWidget;
    auto *trigramRoot = new QVBoxLayout(trigramPage);
    auto *trigramBar = new QHBoxLayout;
    const auto &trigrams = trigramCatalog();
    for (int i = 0; i < trigrams.size(); ++i) {
        auto *btn = new QPushButton(trigrams[i].symbol + QLatin1Char(' ') + trigrams[i].name);
        btn->setCursor(Qt::PointingHandCursor);
        connect(btn, &QPushButton::clicked, this, [this, i] { showTrigram(i); });
        trigramBar->addWidget(btn);
    }
    m_trigramDetail = makeBrowser();
    trigramRoot->addLayout(trigramBar);
    trigramRoot->addWidget(m_trigramDetail, 1);
    m_stack->addWidget(wrap(trigramPage));

    auto *seasonPage = new QWidget;
    auto *seasonRoot = new QVBoxLayout(seasonPage);
    auto *seasonBar = new QHBoxLayout;
    const auto &seasons = seasonCatalog();
    for (int i = 0; i < seasons.size(); ++i) {
        auto *btn = new QPushButton(seasons[i].name + QStringLiteral(" · ") + seasons[i].element);
        btn->setCursor(Qt::PointingHandCursor);
        connect(btn, &QPushButton::clicked, this, [this, i] { showSeason(i); });
        seasonBar->addWidget(btn);
    }
    m_seasonDetail = makeBrowser();
    seasonRoot->addLayout(seasonBar);
    seasonRoot->addWidget(m_seasonDetail, 1);
    m_stack->addWidget(wrap(seasonPage));

    m_stack->addWidget(wrap(makeBrowser(disclaimerHtml())));

    auto *right = new QVBoxLayout;
    auto *foot = new QLabel(QStringLiteral("仅供科普学习，不能替代专业诊疗，亦非占卜。"));
    foot->setObjectName(QStringLiteral("disclaimer"));
    right->addWidget(m_stack, 1);
    right->addWidget(foot);

    root->addWidget(m_nav);
    root->addLayout(right, 1);

    connect(m_nav, &QListWidget::currentRowChanged, m_stack, &QStackedWidget::setCurrentIndex);
    connect(m_phases, &FivePhaseWidget::elementActivated, this, &MainWindow::showElement);

    showElement(0);
    showTrigram(0);
    showSeason(0);
}

void MainWindow::showElement(int index)
{
    const auto &e = elementCatalog().at(index);
    m_elementDetail->setHtml(
        QStringLiteral("<h2>%1 · %2</h2>").arg(e.name, e.nature)
        + QStringLiteral("<p>对应八卦：<b>%1</b></p>").arg(e.trigram)
        + QStringLiteral("<p>藏象：脏 <b>%1</b>，腑 <b>%2</b>；开窍于 <b>%3</b>，在体为 <b>%4</b>。</p>")
              .arg(e.organ, e.fu, e.sense, e.tissue)
        + QStringLiteral("<p>时与情志：季节 <b>%1</b>，情志 <b>%2</b>，五味 <b>%3</b>，五色 <b>%4</b>。</p>")
              .arg(e.season, e.emotion, e.flavor, e.colorName)
        + QStringLiteral("<p>生克：%1%2，%1%3。生克是调节关系，不是简单「谁打倒谁」。</p>")
              .arg(e.name, e.generates, e.restrains)
        + QStringLiteral("<p>%1</p>").arg(e.care)
        + QStringLiteral("<p style='color:#9aa8bd'>这些对应来自《黄帝内经》藏象与五行学说，用来学习功能倾向，不能据此自行诊断。</p>"));
}

void MainWindow::showTrigram(int index)
{
    const auto &t = trigramCatalog().at(index);
    m_trigramDetail->setHtml(QStringLiteral(
        "<h2>%1 %2</h2>"
        "<p>卦德：%3</p>"
        "<p>《说卦》取象：身体部位偏于 <b>%4</b>；功能上常与 <b>%5</b> 对照来读。</p>"
        "<p>%6</p>"
        "<p style='color:#9aa8bd'>取象是比喻系统。头痛不一定是乾卦的问题，腹痛也不等于坤病。</p>")
                                 .arg(t.symbol, t.name, t.nature, t.body, t.organHint, t.meaning));
}

void MainWindow::showSeason(int index)
{
    const auto &s = seasonCatalog().at(index);
    m_seasonDetail->setHtml(QStringLiteral(
        "<h2>%1 · 五行%2</h2>"
        "<p><b>易象：</b>%3</p>"
        "<p><b>养生侧重：</b>%4</p>"
        "<p>经典依据可对照《素问·四气调神大论》：春生、夏长、秋收、冬藏。作息比补品更接近原意。</p>")
                                .arg(s.name, s.element, s.yijing, s.tcm));
}
