/*
 * Copyright (c) 2015-2016 Joshua Snyder
 * Distributed under the GNU GPL v3. For full terms see the file LICENSE
 *
 * This file is part of Shticker Book Rewritten.
 *
 * Shticker Book Rewritten is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shticker Book Rewritten is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Shticker Book Rewritten.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LAUNCHERWINDOW_H
#define LAUNCHERWINDOW_H

#include "loginworker.h"
#include "launcheruser.h"

#include <QObject>
#include <QMainWindow>
#include <QList>

#ifdef __linux__
#include <xdo.h>
#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted
#undef Type
#endif

namespace Ui {
class LauncherWindow;
}

class LauncherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LauncherWindow(QWidget *parent = 0);
    ~LauncherWindow();

private slots:
    void relayMessage(QString);
    void relayProgressBarReceived(int);
    void relayShowProgressBar();
    void relayHideProgressBar();
    void loginReady();
    void initiateLogin();
    void gameHasStarted(qint64);
    void gameHasFinished(int, qint64, QByteArray);
    void authenticationFailed();
    void newsViewLoaded();
    void fillCredentials(int);
    void changeFilePath();
    void updateFiles();
    void updatesReady();
    void toggleAutoUpdates();
    void toggleKeepAlive();
    void runKeepAlive();

signals:
    void sendMessage(QString);
    void sendProgressBarReceived(int);
    void showProgressBar();
    void hideProgressBar();
    void enableLogin(bool);
    void enableUpdate(bool);

private:
    Ui::LauncherWindow *ui;
    bool loginIsReady;
    LoginWorker *loginWorker;
    QList<qint64> gameInstances;
    QThread *updateThread;
    QList<LauncherUser> savedUsers;
    QString filePath;
    QString cachePath;
    bool autoUpdate;
    bool keepAlive;
    QTimer *keepAliveTimer = nullptr;

#ifdef __linux__
    xdo_t *xdo = nullptr;
#endif

    void updateKeepAliveTimer();
    void readSettings();
    void readSettingsPath();
    void writeSettings();
    void setFilePath();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // LAUNCHERWINDOW_H
