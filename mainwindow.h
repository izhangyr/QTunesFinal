/*++=========================
    MainWindow.h
    Mainwindow.cpp
    main.cpp
    glwidget.h
    glwidget.cpp
    audiere.h

    Group Member: Ka Fai Lee, Jonathan Amenechi, and Shifali




++=========================*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include <QFileDialog>
#include <QMessageBox>

#include <QProgressDialog>
#include <QProgressBar>

#include <QMenu>
#include <QAction>

#include <QLabel>

#include <QToolBar>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QListWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QStackedLayout>
#include <QSplitter>
#include <QString>
#include <QSlider>
#include <QLCDNumber>

#include <QListWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QListWidgetItem>

#include <QMenuBar>

#include <QtMultimedia>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class QLCDNumber;
#include "glwidget.h"
class GLWidget;
#include "audiere.h"
using namespace audiere;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class MainWindow : public QMainWindow
{
    Q_OBJECT    // is necessary for all classes that
                // define signals or slots

public:

    MainWindow(QWidget *parent = 0);
    // default is a null pointer, meaning the dialog has no parent
    ~MainWindow();

private slots:

    void            goto_list           ();                 // Switch to QListWdiget page
    void            goto_opengl         ();                 // Switch to OpenGL Visualizer Widget

    void            about               ();                 // Qtunes information
    void            open                ();                 // Opens your Music Folder
    void            traverseDirs        (QString );         // Collect information for music files

    void            populateListWidgets(QList<QStringList>);// Populate QListWidget with files info
    void            populateTableWidget(QList<QStringList>);// Populate QTableWidget with files info

    void            create_playlist     ();                 // Creates a Playlist(for next and previous buttons)

    void            genreClicked        ();                 // Filter other lists based on the genre clicked
    void            artistClicked       ();                 // Filter other lists based on the artist clicked
    void            albumClicked        ();                 // Filter other lists based on the album clicked
    void            listReset           (QListWidget*);     // Reset the lists

    void            play_music          ();                 // Function enable media playing
    void            pause_music         ();                 // Function enable media pause
    void            stop_music          ();                 // Function enable media stop
    void            next_music          ();                 // Playing previous song in playlist
    void            previous_music      ();                 // Playing next song in playlist

    void            volume_icon         ();                 // Mute or Unmute Mediaplayer
    void            volumechanged       (int);              // Adjust Volume according to slider value
    void            tableClicked        (int, int);         // Play certain song when click in tablewidget

    void            update_title        ();                 // Display current media title
    void            durationChanged     (qint64 duration);  // Update element
    void            positionChanged     (qint64 progress);  // Update element
    void            tick                (qint64 time);      // Update time in timedisplay
    void            progress            (qint64 time);      // Update song progress slider

// -------------------------------------------------------------------------------
private:

    void        create_Actions      ();         // Create QActions in Menu_bar
    void        create_Menus        ();         // Create QMenu options in Menu_bar
    void        create_listwidget   ();         // Create QListWidget(Genre,Artist,Album)
    void        create_opengl       ();         // Create GLWidget *m_openglwidget(Visualizer)
    void        create_tablewidget  ();         // Create QTableWidget and detail
    void        create_stacklayout  ();         // Create QStackedLayout(listwidget and Visualizer)
    void        create_utility      ();         // Create Button and other display in upper layout
    void        create_player       ();         // Create and initialize QMediaplayer
    void        create_splitter     ();         // Create QSplitter and connect the Layout

// variables

    QAction         *m_openAction;
    QAction         *m_exitAction;
    QAction         *m_aboutQTAction;
    QAction         *m_aboutQtuneAction;

    QMenu           *m_fileMenu;
    QMenu           *m_aboutMenu;

    QWidget         *m_fullcontainer;
    QHBoxLayout     *m_fullcontainer_layout;

    QVBoxLayout     *m_genrecontainer_layout;
    QLabel          *m_labelGenre;
    QListWidget     *m_listGenre;

    QVBoxLayout     *m_artistcontainer_layout;
    QLabel          *m_labelArtist;
    QListWidget     *m_listArtist;

    QVBoxLayout     *m_albumcontainer_layout;
    QLabel          *m_labelAlbum;
    QListWidget     *m_listAlbum;

    GLWidget       *m_openglwidget;

    QWidget         *m_tablecontainer;
    QVBoxLayout     *m_tablecontainer_layout;
    QTableWidget    *m_songTable;
    QHeaderView     *m_tableheader;

    QWidget         *m_stack;
    QStackedLayout  *m_stacklayout;

    QHBoxLayout     *m_switchingbutton_layout;
    QToolBar        *m_tabbar;
    QToolBar        *m_buttonbar;
    QAction         *m_listwidgetAction;
    QAction         *m_openglAction;

    QAction         *m_playAction;
    QAction         *m_pauseAction;
    QAction         *m_stopAction;
    QSlider         *m_volumeslider;
    QAction         *m_volumeAction;
    QAction         *m_nextAction;
    QAction         *m_previousAction;
    QLabel          *m_NowPlaying;

    QMediaPlayer    *m_player;
    QMediaPlaylist  *m_playlist;
    bool             m_hasSong;

    QHBoxLayout     *m_songinfo_layout;
    QSlider         *m_songslider;
    QLCDNumber      *m_timedisplay;

    QVBoxLayout     *m_toplayout;
    QWidget         *m_topwidget;

    QSplitter       *m_middlesplit;
    QList<QStringList> m_listSongs;

};

#endif // MAINWINDOW_H
