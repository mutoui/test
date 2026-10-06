#pragma once

#include <QMainWindow>

class QListWidget;
class QStackedWidget;
class QLabel;
class QTextBrowser;
class FivePhaseWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void showElement(int index);
    void showTrigram(int index);
    void showSeason(int index);

    QListWidget *m_nav = nullptr;
    QStackedWidget *m_stack = nullptr;
    FivePhaseWidget *m_phases = nullptr;
    QTextBrowser *m_elementDetail = nullptr;
    QTextBrowser *m_trigramDetail = nullptr;
    QTextBrowser *m_seasonDetail = nullptr;
};
