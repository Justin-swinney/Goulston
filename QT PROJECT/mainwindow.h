#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QListWidgetItem>
#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>
#include <QFileSystemWatcher>
#include <QWebEngineView>
#include <QWebChannel>
#include <QJsonDocument>
#include <QVariantMap>
#include <QString>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QRectF>
#include <QGraphicsRectItem>





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_open_page_1_button_clicked();

    void on_return_To_Main_Menu_clicked();

    void on_open_page_2_button_clicked();

    void on_return_To_Main_Menu_2_clicked();

    void on_add_Image_Button_clicked();

    void on_image_list_widget_itemClicked(QListWidgetItem *item);

    void on_remove_Image_Button_clicked();

    void populateImageList();

    void refreshImageList();

    void on_renameButton_clicked();

    void on_image_list_widget_itemDoubleClicked(QListWidgetItem *item);

    void on_search_bar_returnPressed();

    void on_search_button_clicked();

    void on_search_bar_textChanged(const QString &arg1);



    void on_crop_button_clicked();


private:
    Ui::MainWindow *ui;
    QFileSystemWatcher *fileWatcher;
    bool updateButtonClicked = false; // Flag to track whether Update Website button is clicked
    bool imageRemoved = false;
    bool renamingInProgress = false;
    bool searching = false;
    QList<QString> originalImageNames;
    void searchImages(const QString &searchTerm);
    QString searchTerm;
    QString newImagePath;
    QPixmap pixmap;
    QGraphicsPixmapItem* cropBox;
    QString directory = "C:/xampp_lite_5_6/www/myproject/images/";






};

#endif // MAINWINDOW_H
