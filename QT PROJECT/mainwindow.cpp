/* * * * * * * * * * * * * *
 * Justin Swinney          *
 * Goulston Technologies   *
 * 8/10/2023               *
 * * * * * * * * * * * * * */


// #include - all include statments are requried for functionality of code

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>





// Constructor - initializes the main window of this application and sets up user interface.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileWatcher = new QFileSystemWatcher(this); // File watcher - monitor changes in the specified directory
    connect(fileWatcher, &QFileSystemWatcher::directoryChanged, this, &MainWindow::refreshImageList);
    fileWatcher->addPath(directory);
    refreshImageList();
    connect(ui->search_bar, &QLineEdit::returnPressed, this, &MainWindow::on_search_bar_returnPressed);
    connect(ui->search_button, &QPushButton::clicked, this, &MainWindow::on_search_button_clicked);
    connect(ui->search_bar, &QLineEdit::textChanged, this, &MainWindow::on_search_bar_textChanged);



}



MainWindow::~MainWindow()
{
    delete ui;

    disconnect(fileWatcher, &QFileSystemWatcher::directoryChanged, this, &MainWindow::refreshImageList);
    fileWatcher->removePath(directory);
}

void MainWindow::on_open_page_1_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    populateImageList();
}

void MainWindow::on_return_To_Main_Menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_open_page_2_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_return_To_Main_Menu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::refreshImageList()
{
    ui->image_list_widget->clear();

    QDir imageFolder(directory);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    QStringList imageFiles = imageFolder.entryList(filters, QDir::Files);

    foreach (const QString &imageFile, imageFiles) {
        QListWidgetItem *item = new QListWidgetItem();
        QString imageName = QFileInfo(imageFile).completeBaseName();
        item->setText(imageName);
        item->setData(Qt::UserRole, imageFolder.filePath(imageFile));
        ui->image_list_widget->addItem(item);
    }
}

void MainWindow::populateImageList()
{
    ui->image_list_widget->clear();
    originalImageNames.clear(); // Clear the list before populating it

    QDir imageDir(directory);
    QStringList imageFilters;
    imageFilters << "*.png" << "*.jpg" << "*.jpeg";
    QStringList imageFiles = imageDir.entryList(imageFilters);

    foreach (const QString &imageFile, imageFiles) {
        QListWidgetItem *item = new QListWidgetItem();
        QString imageName = QFileInfo(imageFile).completeBaseName();
        originalImageNames.append(imageName.toLower()); // Store lowercase name in the list
        item->setText(imageName);
        item->setData(Qt::UserRole, imageDir.filePath(imageFile));
        ui->image_list_widget->addItem(item);
    }
}

void MainWindow::on_add_Image_Button_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Add Image", "", "Images (*.png *.jpg *.jpeg)");

    if (!imagePath.isEmpty()) {
        bool ok;
        QString imageName = QInputDialog::getText(this, "Enter Image Name", "Enter a name for the image:", QLineEdit::Normal, QString(), &ok, Qt::MSWindowsFixedSizeDialogHint);

        if (ok && !imageName.isEmpty()) {
            // Ensure that the new image name has a valid file extension
            QString fileExtension = QFileInfo(imagePath).suffix();
            if (fileExtension.isEmpty()) {
                qDebug() << "Invalid file extension for the selected image.";
                return;
            }

            // Construct the full destination file path
            newImagePath = "C:/xampp_lite_5_6/www/myproject/images/" + imageName + "." + fileExtension;

            // Check if an image with the same name already exists in the list
            bool alreadyExists = false;
            for (int i = 0; i < ui->image_list_widget->count(); ++i) {
                QListWidgetItem *item = ui->image_list_widget->item(i);
                QString existingName = item->text();
                if (existingName == imageName) {
                    alreadyExists = true;
                    break;
                }
            }

            if (alreadyExists) {
                qDebug() << "Image with the same name already exists in the list.";
                return;
            }

            if (QFile::copy(imagePath, newImagePath)) {
                QListWidgetItem *item = new QListWidgetItem();
                item->setText(imageName);
                item->setData(Qt::UserRole, newImagePath);
                ui->image_list_widget->addItem(item);


            } else {
                qDebug() << "Failed to copy image.";
            }
        }
    }
}
void MainWindow::on_image_list_widget_itemClicked(QListWidgetItem *item)
{
    QString imagePath = item->data(Qt::UserRole).toString();
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        qreal scaleFactor = QApplication::primaryScreen()->devicePixelRatio();
        QSize targetSize(static_cast<int>(300 * scaleFactor), static_cast<int>(400 * scaleFactor));
        pixmap = pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Set the pixmap with the updated image
        ui->imageLabel->setPixmap(pixmap);

        // Adjust the size policy to ensure the label resizes properly
        ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
}

void MainWindow::on_remove_Image_Button_clicked()
{
    QListWidgetItem *selectedItem = ui->image_list_widget->currentItem();

    if (selectedItem) {
        QString imagePath = selectedItem->data(Qt::UserRole).toString();
        QFile file(imagePath);

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Removal", "Are you sure you want to remove this image?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            if (file.remove()) {
                qDebug() << "File removed successfully: " << imagePath;
                delete selectedItem;
                ui->imageLabel->clear();
            } else {
                qDebug() << "Failed to remove file: " << imagePath;
            }
        }
    }
}



void MainWindow::on_renameButton_clicked()
{
    QListWidgetItem *selectedItem = ui->image_list_widget->currentItem();
    if (!selectedItem)
        return;

    bool ok;
    QString newName = QInputDialog::getText(this, "Rename Image", "Enter a new name for the image:", QLineEdit::Normal, selectedItem->text(), &ok, Qt::MSWindowsFixedSizeDialogHint);

    if (ok && !newName.isEmpty()) {
        QString imagePath = selectedItem->data(Qt::UserRole).toString();
        QString newImagePath = QFileInfo(imagePath).dir().absoluteFilePath(newName + "." + QFileInfo(imagePath).suffix());

        if (QFile::rename(imagePath, newImagePath)) {
            selectedItem->setText(QFileInfo(newImagePath).completeBaseName());
            selectedItem->setData(Qt::UserRole, newImagePath);
        } else {
            qDebug() << "Failed to rename image.";
        }
    }
}

void MainWindow::on_image_list_widget_itemDoubleClicked(QListWidgetItem *item)
{
    if (renamingInProgress) {
        return;
    }

    renamingInProgress = true;

    bool ok;
    QString newName = QInputDialog::getText(this, "Rename Image", "Enter a new name for the image:", QLineEdit::Normal, item->text(), &ok, Qt::MSWindowsFixedSizeDialogHint);

    if (ok && !newName.isEmpty()) {
        QString imagePath = item->data(Qt::UserRole).toString();
        QString newImagePath = QFileInfo(imagePath).dir().absoluteFilePath(newName + "." + QFileInfo(imagePath).suffix());

        if (QFile::rename(imagePath, newImagePath)) {
            item->setText(QFileInfo(newImagePath).completeBaseName());
            item->setData(Qt::UserRole, newImagePath);
        } else {
            qDebug() << "Failed to rename image.";
        }
    }

    renamingInProgress = false;
}

void MainWindow::on_search_button_clicked()
{
    QString searchTerm = ui->search_bar->text().trimmed().toLower();

    if (searchTerm.isEmpty()) {
        // Reset the list to show all items if the search term is empty
        refreshImageList();
        searching = false;
    } else {
        // Perform the search and show matching items
        searchImages(searchTerm);
        searching = true;
    }
}
void MainWindow::on_search_bar_returnPressed()
{
    QString searchTerm = ui->search_bar->text().trimmed().toLower();
    searchImages(searchTerm);
}

void MainWindow::searchImages(const QString &searchTerm)
{
    ui->image_list_widget->clear();

    QDir imageFolder(directory);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    QStringList imageFiles = imageFolder.entryList(filters, QDir::Files);

    foreach (const QString &imageFile, imageFiles) {
        QString imageName = QFileInfo(imageFile).completeBaseName().toLower(); // Convert to lower case for case-insensitive comparison
        if (imageName.contains(searchTerm)) {
            QListWidgetItem *item = new QListWidgetItem();
            item->setText(QFileInfo(imageFile).completeBaseName());
            item->setData(Qt::UserRole, imageFolder.filePath(imageFile));
            ui->image_list_widget->addItem(item);
        }
    }
}

void MainWindow::on_search_bar_textChanged(const QString &arg1)
{
    searchTerm = arg1.trimmed().toLower(); // Update the searchTerm variable with the new text

    if (searchTerm.isEmpty()) {
        // Reset the list to show all items if the search term is empty
        refreshImageList();
        searching = false;
    } else {
        // Perform the search and show matching items
        QListWidgetItem* item;
        for (int i = 0; i < ui->image_list_widget->count(); ++i) {
            item = ui->image_list_widget->item(i);
            if (item->text().toLower().contains(searchTerm.toLower())) {
                item->setHidden(false);
            } else {
                item->setHidden(true);
            }
        }
        searching = true;
    }
}

void MainWindow::on_crop_button_clicked() {}



