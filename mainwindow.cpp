#include <QtGui>
#include "mainwindow.h"
// #include "glwidget.h"

enum {PATH,TITLE,ARTIST,ALBUM,GENRE,TRACK,TIME,COLS};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    create_Actions              ();	// Create QActions for QMenu

    create_Menus                (); // Create QMenu options

    create_listwidget           ();	// Create QListWidget ~~ m_fullcontainer

    create_opengl               (); // Create Opengl Tab ~~ m_openglcontainer

    create_stacklayout          (); // Create QStackedLayout ~~ m_switching(both list and opengl)

    create_tablewidget          (); // Create QTableWidget ~~ m_tablecontainer

    create_utility              (); // Create QButtons choice on top

    create_player               (); // Create QMediaPlayer

    create_splitter             (); // Create QSplitter ~~(buttons, switching, table)

    // Connection to activate visualizer
    // trigger when play()
    connect(m_songTable, SIGNAL(cellDoubleClicked(int,int)),m_openglwidget, SLOT(startTime()));
    connect(m_playAction, SIGNAL(triggered()),m_openglwidget, SLOT(startTime()));

    // stop when pause or stop
    connect(m_pauseAction, SIGNAL(triggered()),m_openglwidget, SLOT(endTime()));
    connect(m_stopAction, SIGNAL(triggered()),m_openglwidget, SLOT(endTime()));


    // Set Central Widget to m_middlesplit
    setCentralWidget(m_middlesplit);

    // Set Window Title to "Qtune"
    setWindowTitle("QTunes");
}
MainWindow::~MainWindow()
{

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// createActions():
//
// create and connect all menu actions.
//
void MainWindow::create_Actions()
{
    // QAction available to open music file directory   (Open)
    m_openAction = new QAction("Open", this);
        connect(m_openAction, SIGNAL(triggered()), this, SLOT(open()));

    // QAction that exit the program    (Quit)
    m_exitAction = new QAction("Exit", this);
        connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Messagebox about the Qt version information  (About_Qt)
    m_aboutQTAction = new QAction("About QT", this);
        connect(m_aboutQTAction, SIGNAL(triggered()),qApp, SLOT(aboutQt()));

    // MessageBox about this media program  (About_Qtune)
    m_aboutQtuneAction = new QAction("About QTune", this);
        connect(m_aboutQtuneAction, SIGNAL(triggered()),this, SLOT(about()));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// createMenus():
//
// create all menu options, and add action into menu
//
void MainWindow::create_Menus()
{
    // Create and Add new Menu option "File"
    m_fileMenu = menuBar()->addMenu(tr("&File"));

    // Add Actions "Open" and "Exit"
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addAction(m_exitAction);

    // Create and Add new Menu option "About"
    m_aboutMenu = menuBar()->addMenu("About");

    // Add Actions "About_Qt" and "About_Qtune"
   m_aboutMenu->addAction(m_aboutQTAction);
   m_aboutMenu->addAction(m_aboutQtuneAction);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// create_listwidget():
//
// create the three listwidgets. End product is m_fullcontainer (ListWidget Tab)
//
//
void MainWindow::create_listwidget()
{
    // Create VBoxLayout that contains Label"Genre" and Genre ListWidget
    m_genrecontainer_layout = new QVBoxLayout;
    m_labelGenre = new QLabel("Genre");
    m_listGenre = new QListWidget;

    // Init first item and set current row as 0
    m_listGenre->addItem("All");
    m_listGenre->setCurrentRow(0);

    // QObject::
    // Song filter when click item in genre list
    connect(m_listGenre,SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(genreClicked()));

    // Adding label and listwidget into m_genrecontainer_layout
    m_genrecontainer_layout->addWidget(m_labelGenre);
    m_genrecontainer_layout->addWidget(m_listGenre);

    // Create VBoxLayout that contains Label"Artist" and Artist ListWidget
    m_artistcontainer_layout = new QVBoxLayout;
    m_labelArtist = new QLabel("Artist");
    m_listArtist = new QListWidget;

    // Init first item and set current row as 0
    m_listArtist->addItem("All");
    m_listArtist->setCurrentRow(0);

    // Song filter when click item in artist list
    connect(m_listArtist,SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(artistClicked()));

    // Adding label and listwidget into m_artistcontainer_layout
    m_artistcontainer_layout->addWidget(m_labelArtist);
    m_artistcontainer_layout->addWidget(m_listArtist);

    // Create VBoxLayout that contains Label"Album" and Album ListWidget
    m_albumcontainer_layout = new QVBoxLayout;
    m_labelAlbum = new QLabel("Album");
    m_listAlbum = new QListWidget;

    // Init first item and set current row as 0
    m_listAlbum->addItem("All");
    m_listAlbum->setCurrentRow(0);

    // Song filter when click item in album list
    connect(m_listAlbum,SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(albumClicked()));

    // Adding label and listwidget into m_albumcontainer_layout
    m_albumcontainer_layout->addWidget(m_labelAlbum);
    m_albumcontainer_layout->addWidget(m_listAlbum);

    // Create a HBoxLayout that contain all listwidget layout
    m_fullcontainer_layout = new QHBoxLayout;
    m_fullcontainer_layout->addLayout(m_genrecontainer_layout);
    m_fullcontainer_layout->addLayout(m_artistcontainer_layout);
    m_fullcontainer_layout->addLayout(m_albumcontainer_layout);

    // Create a widget and set its layout to m_fullcontainer_layout
    m_fullcontainer = new QWidget;
    m_fullcontainer->setLayout(m_fullcontainer_layout);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// create_opengl():
//
// create the opengl tab. End product is m_opengl (OpenGL Tab)
//
void MainWindow::create_opengl()
{
    // Create new GLWidget m_openglwidget from glwidget class
    m_openglwidget = new GLWidget;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// create_stacklayout():
//
// create the stackedlayout and connect the two page.
//
void MainWindow::create_stacklayout()
{
    // Create QStackedLayout and new QWidget
    m_stack = new QWidget;
    m_stacklayout = new QStackedLayout;

    // add the two widgets inside switching layout
    m_stacklayout->addWidget(m_fullcontainer);
    m_stacklayout->addWidget(m_openglwidget);

    // Set m_stacklayout to m_stack, has the listwidget(0) and visualizer(1)
    m_stack->setLayout(m_stacklayout);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// create_tablewidget():
//
// create the tablewidget. End product is m_tablecontainer
//
void MainWindow::create_tablewidget()
{
    // Create TableWidget and widget
    m_tablecontainer = new QWidget;
    m_tablecontainer_layout = new QVBoxLayout;

    // Create TableWidget and headerview
    m_songTable = new QTableWidget(0, 7);
    m_tableheader = new QHeaderView(Qt::Horizontal,m_songTable);

    m_tableheader->setSectionResizeMode(QHeaderView::Stretch);  // Qt 5

    // Set the horizontalheader and set header labels
    m_songTable->setHorizontalHeader(m_tableheader);
    m_songTable->setHorizontalHeaderLabels(QStringList() <<
        "Title" << "Artist" << "Album" << "Genre" << "Track" << "Time" << "Path");

    // Set up restriction and function
    m_songTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_songTable->setAlternatingRowColors(1);
    m_songTable->setShowGrid(1);
    m_songTable->setEditTriggers (QAbstractItemView::NoEditTriggers);
    m_songTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    // set Column 6 (Path) hidden
    m_songTable->setColumnHidden(6,true);

    // play song if clikced on the table
    connect(m_songTable, SIGNAL(cellDoubleClicked(int,int)),this, SLOT(tableClicked(int,int)));

    // Add m_songTable into layout and set layout into widget
    m_tablecontainer_layout->addWidget(m_songTable);
    m_tablecontainer->setLayout(m_tablecontainer_layout);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// create_utility():
//
// create utilities buttons on top of the MainWindow
//
void MainWindow::create_utility()
{
    // Create QAction that switch to Listwidget layout(tab)
    m_listwidgetAction = new QAction(style()->standardIcon(QStyle::SP_ArrowLeft), tr("Listwidget"), this);
        connect(m_listwidgetAction, SIGNAL(triggered()),this, SLOT(goto_list()));

    // Create QAction that switch to OpenGL layout(tab)
    m_openglAction = new QAction(style()->standardIcon(QStyle::SP_ArrowRight), tr("OpenGL"), this);
        connect(m_openglAction, SIGNAL(triggered()),this, SLOT(goto_opengl()));

    // Create QAction that provide play button option
    m_playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
        connect(m_playAction, SIGNAL(triggered()),this, SLOT(play_music()));

    // Create QAction that provide pause button option
    m_pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
        connect(m_pauseAction, SIGNAL(triggered()),this, SLOT(pause_music()));

    // Create QAction that provide stop button option
    m_stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
        connect(m_stopAction, SIGNAL(triggered()),this, SLOT(stop_music()));

    // volume slider for QMediaPlayer
    m_volumeslider = new QSlider(Qt::Horizontal, this);
    m_volumeslider->setRange(0, 100);
    m_volumeslider->setValue(50);
    connect(m_volumeslider, SIGNAL(valueChanged(int)), this, SLOT(volumechanged(int)));

    // Create QAction that provide volume button option(mute or unmute)
    m_volumeAction = new QAction(style()->standardIcon(QStyle::SP_MediaVolume), tr("Volume"), this);
        connect(m_volumeAction, SIGNAL(triggered()),this, SLOT(volume_icon()));

    // Create QAction for next song in the playlist
    m_nextAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipForward), tr("Next"), this);
        connect(m_nextAction, SIGNAL(triggered()),this, SLOT(next_music()));

    // Create QAction for previous song in the playlist
    m_previousAction = new QAction(style()->standardIcon(QStyle::SP_MediaSkipBackward), tr("Previous"), this);
        connect(m_previousAction, SIGNAL(triggered()),this, SLOT(previous_music()));

    // Create QLabel(status of Mediaplayer)
    m_NowPlaying = new QLabel("Qtune Media Player");
    m_NowPlaying->setMaximumWidth(150);
    m_NowPlaying->setMinimumWidth(150);

 // Create new Toolbar and add all actions aboove
    m_tabbar = new QToolBar;
    m_tabbar->addAction(m_listwidgetAction);
    m_tabbar->addAction(m_openglAction);

    m_buttonbar = new QToolBar;
    m_buttonbar->addAction(m_previousAction);
    m_buttonbar->addAction(m_playAction);
    m_buttonbar->addAction(m_pauseAction);
    m_buttonbar->addAction(m_stopAction);
    m_buttonbar->addAction(m_nextAction);
    m_buttonbar->addAction(m_volumeAction);

    // Create QVBoxLayout and Widget
    //m_switchingbutton = new QWidget;
    m_switchingbutton_layout = new QHBoxLayout;

    // Add toolbar to layout and set layout into widget
    m_switchingbutton_layout->addWidget(m_tabbar);
    m_switchingbutton_layout->addWidget(m_NowPlaying);
    m_switchingbutton_layout->addWidget(m_buttonbar);
    m_switchingbutton_layout->addWidget(m_volumeslider);
    m_switchingbutton_layout->addStretch(5);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// create_player();
//
// Create QMediaPlayer
//
//
void MainWindow::create_player()
{
    // Create new Media Player
    m_player = new QMediaPlayer;

    // Create new playlist
    m_playlist = new QMediaPlaylist;
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

    // boolean variable for functions
    m_hasSong = false;

    // Create time display of the media
    m_timedisplay = new QLCDNumber;
    m_timedisplay->display("00:00");

    // Self defined functions
    connect(m_player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));

    // the m_timedisplay updater
    connect(m_player, SIGNAL(positionChanged(qint64)),this, SLOT(tick(qint64)));

    // Song Progress slider
    m_songslider = new QSlider(Qt::Horizontal, this);

    // the song progress slider updater
    connect(m_player, SIGNAL(positionChanged(qint64)),this, SLOT(progress(qint64)));

    // HBoxLayout for songslider(progress) and timedisplay(progress)
    m_songinfo_layout = new QHBoxLayout;
    m_songinfo_layout->addWidget(m_songslider);
    m_songinfo_layout->addWidget(m_timedisplay);

    // Another Layout containing buttons and songinfo layout
    m_toplayout = new QVBoxLayout;
    m_topwidget = new QWidget;
    m_toplayout->addLayout(m_switchingbutton_layout);
    m_toplayout->addLayout(m_songinfo_layout);

    // final product of the top layout
    m_topwidget->setLayout(m_toplayout);

}

void MainWindow::create_splitter()
{
    // Create Splitter
    m_middlesplit = new QSplitter;
    m_middlesplit->setOrientation(Qt::Vertical);

    // Create Splitter between the buttonlayout, listwidget/opengl and tablewidget
    m_middlesplit->addWidget(m_topwidget);
    m_middlesplit->addWidget(m_stack);
    m_middlesplit->addWidget(m_tablecontainer);


}

void MainWindow::goto_list()
{
    m_stacklayout->setCurrentIndex(0);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// goto_opengl():
//
// change to opengl tab.
//
void MainWindow::goto_opengl()
{
    m_stacklayout->setCurrentIndex(1);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// about():
//
// MessageBox that shows information
//
void MainWindow::about()
{
    QMessageBox::information(this, tr("About QTune Prototype 1.0"),
         tr("The QTunes Prototype is a basic music player. It uses the audiere library to process the relevant tags from the songs. We have also implemented a basic visualizer."));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// open()
//
// the menu option for process song information
//
void MainWindow::open()
{
    QString path = QFileDialog::getExistingDirectory(this, "Choose Folder",
            "C:/Users/", QFileDialog::ShowDirsOnly);
    traverseDirs(path);
    m_hasSong = true;

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// traverseDirs(QString path):
//
// process the directory's songs information.
//

void MainWindow::traverseDirs(QString path)
{
    QString		key, val;
    QStringList	list;

    // init listDirs with subdirectories of path
    QDir dir(path);
    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QFileInfoList listDirs = dir.entryInfoList();

    // init listFiles with all *.mp3 files in path

    QDir files(path);
    files.setFilter(QDir::Files);
    files.setNameFilters(QStringList("*.mp3"));
    QFileInfoList listFiles = files.entryInfoList();

    for(int i=0; i < listFiles.size(); i++)
    {
        // init list with default values: ""
        for(int j=0; j<=COLS; j++)
            list.insert(j, "");

        // store file pathname into 0th position in list
        QFileInfo fileInfo = listFiles.at(i);
        list.replace(PATH, fileInfo.filePath());

        // convert it from QString to Ascii and store in source, replace toLatin1() to toAscii()
        SampleSourcePtr source = OpenSampleSource(
                     fileInfo.filePath().toLatin1());

        // error checking
        if(!source || source->getTagCount() == 0) continue;

        // process all song tags
        for(int j=0; j<source->getTagCount(); j++)
        {
            // get tag key and value
            key =  source->getTagKey  (j);
            val =  source->getTagValue(j);
            if(val.isEmpty()  ) val = "Unknown";

            // store tag value in proper position in list
            if(key == "genre" ) list.replace(GENRE , val);
            if(key == "artist") list.replace(ARTIST, val);
            if(key == "album" ) list.replace(ALBUM , val);
            if(key == "title" ) list.replace(TITLE , val);
            if(key == "track" ) list.replace(TRACK , val);
            if(key == "time"  ) list.replace(TIME  , val);
        }

        // append list (song data) into songlist m_listSongs;
        m_listSongs << list;
    }

    // Populate QListWidgets and QTableWidget
    populateListWidgets(m_listSongs);
    populateTableWidget(m_listSongs);
    return;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// populateListWidgets():
//
// add songs information into list widget
//

void MainWindow::populateListWidgets(QList<QStringList> m_listSongs)
{
    // Create three QStringList
    QStringList genreList;
    QStringList albumList;
    QStringList artistList;

    // fill in stringlist with files information
    for(int i = 0; i<m_listSongs.size(); i++)
    {
        for(int j = 0;j<COLS; j++)
        {

            genreList << m_listSongs.at(i).at(GENRE);
            albumList << m_listSongs.at(i).at(ALBUM);
            artistList << m_listSongs.at(i).at(ARTIST);
        }
    }

    // Remove any duplicate
    genreList.removeDuplicates();
    albumList.removeDuplicates();
    artistList.removeDuplicates();

    // Add all the QStringList into corresponding listwidget
    m_listGenre->addItems(genreList);
    m_listAlbum->addItems(albumList);
    m_listArtist->addItems(artistList);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// populateTableWidget():
//
// add songs information into tablewidget
//
void MainWindow::populateTableWidget(QList<QStringList> m_listSongs)
{
    // count number of music files and set that to rowcount(tablewidget)
    m_songTable->setRowCount(m_listSongs.size());

    for(int i =0; i<m_listSongs.size(); i++)
    {
    // enum {PATH,TITLE, ARTIST, ALBUM, GENRE, TRACK, TIME,COLS};
        //    0    1      2       3      4       5     6     7

            QTableWidgetItem* col0 = new QTableWidgetItem(m_listSongs.at(i).at(PATH));
            QTableWidgetItem* col1 = new QTableWidgetItem(m_listSongs.at(i).at(TITLE));
            QTableWidgetItem* col2 = new QTableWidgetItem(m_listSongs.at(i).at(ARTIST));
            QTableWidgetItem* col3 = new QTableWidgetItem(m_listSongs.at(i).at(ALBUM));
            QTableWidgetItem* col4 = new QTableWidgetItem(m_listSongs.at(i).at(GENRE));
            QTableWidgetItem* col5 = new QTableWidgetItem(m_listSongs.at(i).at(TRACK));
            QTableWidgetItem* col6 = new QTableWidgetItem(m_listSongs.at(i).at(TIME));

            m_songTable->setItem(i,0,col1);
            m_songTable->setItem(i,1,col2);
            m_songTable->setItem(i,2,col3);
            m_songTable->setItem(i,3,col4);
            m_songTable->setItem(i,4,col5);
            m_songTable->setItem(i,5,col6);
            m_songTable->setItem(i,6,col0);
    }

    // Create playlist
    create_playlist();

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  create_playlist();
//
//  init the starting playlist (call only once)
//
void MainWindow::create_playlist()
{

    int number = m_songTable->rowCount();
    for(int i = 0; i < number;i++)
    {
        // Take the text from "PATH" and use that to add song into playlist
        QString path_text = m_songTable->item(i,6)->text();
        QMediaContent temp = QMediaContent(path_text);
        m_playlist->addMedia(temp);
    }
    m_player->setPlaylist(m_playlist);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  genreClicked()();
//
//  click an item in the Genre ListWidget, filter list and table
//
void MainWindow::genreClicked()
{
    // stores the text of the clicked item
    QString clickedText = m_listGenre->currentItem()->text();

    for(int i = 0; i<m_songTable->rowCount(); i++)
    {
        // resets all the TableWidgetItem's to visible.
        m_songTable->showRow(i);

         // stores the Genre of the ith row
        QString curGenre = m_songTable->item(i,3)->text();

        //"All" item resets the items in the TableWidget and ListWidget
        if(clickedText == "All")
        {
            m_songTable->showRow(i);
            listReset(m_listArtist);
        }

        if((clickedText != curGenre)&&(clickedText!= "All"))
        {
            // Gets the Artist value of the row about to be hidden
            QString currentArtist = m_songTable->item(i,1)->text();

            int count = m_listArtist->count();

            // Goes through the Artist ListWidget and looks for the value of the artist to be hidden
            for(int j = 1; j< count; j++)
            {
                QString artistVal = m_listArtist->item(j)->text();
                if(currentArtist == artistVal)
                {
                    m_listArtist->item(j)->setHidden(true);
                }
            }
        // Hides the row of the TableWidget
        m_songTable->hideRow(i);
        }
    }
    //
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  artistClicked();
//
//  Filter function, based on the artist clicked
//
void MainWindow::artistClicked()
{
    // stores the text of the clicked item
    QString clickedText = m_listArtist->currentItem()->text();

    for(int i = 0; i<m_songTable->rowCount(); i++)
    {
        // resets all the TableWidgetItem's to visible.
        m_songTable->showRow(i);

        // stores the Artist of the ith row
        QString curArtist = m_songTable->item(i,1)->text();

        // The "All" item resets the items in the TableWidget and ListWidget
        if(clickedText == "All")
        {
            m_songTable->showRow(i);

            // Checks if the item in the ListWidget is hidden and sets it to visible
            listReset(m_listArtist);
            listReset(m_listAlbum);
        }
        if((clickedText != curArtist)&&(clickedText!= "All"))
        {
            // Gets the Album value of the row about to be hidden
            QString currentAlbum = m_songTable->item(i,2)->text();

            int count = m_listAlbum->count();

            // Goes through the Album ListWidget and looks for the value of the Album to be hidden
            for(int j = 1; j< count; j++)
            {
                QString albumVal = m_listAlbum->item(j)->text();
                if(currentAlbum == albumVal)
                {
                    // Hides the item in the Album ListWidget
                    m_listAlbum->item(j)->setHidden(true);
                }
            }
            // Hides the row of the TableWidget
            m_songTable->hideRow(i);
        }
    }

//
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  albumClicked();
//
//  click an item in the Album ListWidget, filter list and table
//
void MainWindow::albumClicked()
{
    QString clickedText = m_listAlbum->currentItem()->text();
    for(int i = 0; i<m_songTable->rowCount(); i++)
    {
        m_songTable->showRow(i);
        QString curAlbum = m_songTable->item(i,2)->text();

        if(clickedText == "All")
        {
                m_songTable->showRow(i);
                listReset(m_listAlbum);
        }
        if((clickedText != curAlbum)&&(clickedText!= "All"))
        {
            m_songTable->hideRow(i);
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  listReset(QListWidget* listWidget)
//
//  Checks if the item in the ListWidget is hidden and sets it to visible
//
void MainWindow::listReset(QListWidget* listWidget)
{
    for(int j =0; j<listWidget->count(); j++)
    {
        if(listWidget->item(j)->isHidden())
            listWidget->item(j)->setHidden(false);
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  play_music();
//
//  play current media and call update_title
//
void MainWindow::play_music()
{
    if(m_hasSong)
    {
        m_player->play();
        update_title();
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  pause_music()
//
//  pause current media and set status label to "pause"
//
void MainWindow::pause_music()
{
    if(m_hasSong)
    {
        m_player->pause();
        m_NowPlaying->setText("Pause");
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  stop_music()
//
//  stop current media and set status label to "stop"
//
void MainWindow::stop_music()
{
    if(m_hasSong)
    {
        m_player->stop();
        m_NowPlaying->setText("Stop");
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  next_music()
//
//  go to the next song in playlist
//
void MainWindow::next_music()
{
    if(m_hasSong)
    {m_playlist->next();
        play_music();

    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  previous_music()
//
//  go to the previous song in playlist
//
void MainWindow::previous_music()
{
    if(m_hasSong)
    {m_playlist->previous();
        play_music();
        // update_image();
    }
        // update_title();}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  volume_icon()
//
//  set Mute or Unmute
//
void MainWindow::volume_icon()
{
    if(m_player->isMuted())
         m_player->setMuted(false) ;
    else
        m_player->setMuted(true);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  volumechanged()
//
//  adjust volume according to volume slider
//
void MainWindow::volumechanged(int volume)
{
    m_player->setVolume(volume);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  tableClicked();
//
//  play the selected song in the tablewidget
//
void MainWindow::tableClicked(int row, int column)
{
    stop_music();
    m_playlist->setCurrentIndex(row);
    play_music();
}




// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  update_title();
//
//  update status label
//
void MainWindow::update_title()
{

    if(m_hasSong)
    {
        int ghost = m_playlist->currentIndex();
        // QLabel * current_title = new QLabel(m_songTable->item(ghost,2)->text());
        m_NowPlaying->setText(m_songTable->item(ghost,0)->text());}

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  durationChanged(qint64 duration);
//
//  update duration of the media
//
void MainWindow::durationChanged(qint64 duration)
{
    // run everytime the song changes
    update_title();
    m_songslider->setRange(0, m_player->duration()/1000);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  positionChanged(qint64 progress);
//
//  update position of the media(built-in)
//

void MainWindow::positionChanged(qint64 progress)
{

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  tick(qint64 time);
//
//  update time in timedisplay
//
void MainWindow::tick(qint64 time)
{
    // (in milliseconds) 1s = 1k ms
    QTime displayTime(0, (time / 60000), (time / 1000) % 60);
    m_timedisplay->display(displayTime.toString("mm:ss"));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  progress(qint64 time);
//
//  update limit or value of the songslider
//      (otherwise, slider finish before song finish)
//
void MainWindow::progress(qint64 time)
{
    // set slider in interval of seconds
    m_songslider->setValue(time / 1000);
}
