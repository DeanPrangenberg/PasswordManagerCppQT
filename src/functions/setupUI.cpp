//
// Created by prang on 07.07.2024.
//

#include "../MainWindow/MainWindow.h"


void MainWindow::setupTopbar() {
    int topbarHeight = 40;

    _topBarWidget = new QWidget(this);
    _topBarLayout = new QHBoxLayout(_topBarWidget);

    _inputSearch = new QLineEdit(this);
    _inputSearch->setFixedHeight(topbarHeight);

    _ButtonStartSearch = new QPushButton("search", this);
    _ButtonStartSearch->setFixedHeight(topbarHeight);

    _ButtonReload = new QPushButton("reload", this);
    _ButtonReload->setFixedHeight(topbarHeight);

    _topBarLayout->addWidget(_inputSearch);
    _topBarLayout->addWidget(_ButtonStartSearch);
    _topBarLayout->addWidget(_ButtonReload);

    _topBarWidget->setGeometry(210, 0, _screenWidth - 210, 100);

    _topBarWidget->hide();
    connect(_ButtonStartSearch, SIGNAL(clicked()), this, SLOT(searchInList()));
    connect(_ButtonReload, SIGNAL(clicked()), this, SLOT(reloadList()));
}

void MainWindow::setupSidebar() {
    // Geometric
    int logoHeight = 100;
    int logoWidth = 210;
    int spacingButtonSidebar = 10;
    int spacingSide = 10;
    int buttonsInSideBar = 7;
    int buttonWidthSidebar = logoWidth - spacingSide;
    int buttonHeightSidebar =
            (_screenHeight - logoHeight - spacingButtonSidebar * (buttonsInSideBar + 1)) / buttonsInSideBar;

    // Logo
    _LabelLogo = new QLabel(this);
    QPixmap pixmap("../res/password-manager-logo-img.png");
    pixmap = pixmap.scaled(logoWidth, logoHeight, Qt::KeepAspectRatio);
    _LabelLogo->setPixmap(pixmap);
    _LabelLogo->setAlignment(Qt::AlignCenter);
    _LabelLogo->setFixedSize(logoWidth, logoHeight);

    // Sidebar area
    _sideBarWidget = new QWidget(this);
    _sideBarWidget->setFixedWidth(buttonWidthSidebar);

    _sideBarLayout = new QVBoxLayout(_sideBarWidget);
    _sideBarLayout->setSpacing(spacingButtonSidebar);
    _sideBarLayout->setContentsMargins(spacingSide, spacingSide, spacingSide, spacingSide);

    _ButtonAddEntry = new QPushButton("Add Entry", _sideBarWidget);
    _ButtonAddEntry->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonAddEntry);

    _ButtonShowPasswords = new QPushButton("Show Passwords", _sideBarWidget);
    _ButtonShowPasswords->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonShowPasswords);

    _ButtonShowPasswordGen = new QPushButton("Password Gen", _sideBarWidget);
    _ButtonShowPasswordGen->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonShowPasswordGen);

    _ButtonDelPassword = new QPushButton("Delete Password", _sideBarWidget);
    _ButtonDelPassword->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonDelPassword);

    _ButtonEditPassword = new QPushButton("Edit Password", _sideBarWidget);
    _ButtonEditPassword->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonEditPassword);

    _ButtonChangeMasterPassword = new QPushButton("Change Master", _sideBarWidget);
    _ButtonChangeMasterPassword->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonChangeMasterPassword);

    _ButtonOpenLockscreen = new QPushButton("Close Menu", _sideBarWidget);
    _ButtonOpenLockscreen->setFixedSize(buttonWidthSidebar, buttonHeightSidebar);
    _sideBarLayout->addWidget(_ButtonOpenLockscreen);

    _sideBarWidget->setLayout(_sideBarLayout);
    _sideBarWidget->setGeometry(spacingSide, logoHeight, logoWidth, _screenHeight - logoHeight);

    connect(_ButtonShowPasswordGen, SIGNAL(clicked()), this, SLOT(showPasswordGen()));
    connect(_ButtonOpenLockscreen, SIGNAL(clicked()), this, SLOT(lockScreen()));
    connect(_ButtonShowPasswords, SIGNAL(clicked()), this, SLOT(showPasswords()));
    connect(_ButtonChangeMasterPassword, SIGNAL(clicked()), this, SLOT(showMasterPasswordEdit()));
    connect(_ButtonEditPassword, SIGNAL(clicked()), this, SLOT(showEditPassword()));
    connect(_ButtonDelPassword, SIGNAL(clicked()), this, SLOT(showPasswordDel()));
    connect(_ButtonAddEntry, SIGNAL(clicked()), this, SLOT(showAddEntry()));

    _sideBarWidget->hide();
    _LabelLogo->hide();
}

void MainWindow::setupPasswordEdit() {
    int textLabelWidth = 130;

    _centerNormPasswordEdit = new QWidget(this);
    QVBoxLayout * mainLayout = new QVBoxLayout(_centerNormPasswordEdit);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Top section for input and search
    QGroupBox * inputGroup = new QGroupBox("Edit Password Entry", this);
    inputGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 18px; }");
    QVBoxLayout * inputLayout = new QVBoxLayout(inputGroup);

    // Row number input and search button
    QHBoxLayout * rowLayout = new QHBoxLayout();
    QLabel *rowLabel = new QLabel("Row Number:", this);
    _inputRowEdit = new QLineEdit(this);
    QPushButton *searchRowEditButton = new QPushButton("Search", this);

    rowLayout->addWidget(rowLabel);
    rowLayout->addWidget(_inputRowEdit);
    rowLayout->addWidget(searchRowEditButton);

    // New name, username, and password inputs
    QHBoxLayout * nameInputLayout = new QHBoxLayout();
    QLabel *newNameLabel = new QLabel("Name/Website:", this);
    _inputNewName = new QLineEdit(this);

    nameInputLayout->addWidget(newNameLabel);
    nameInputLayout->addWidget(_inputNewName);

    QHBoxLayout * usernameInputLayout = new QHBoxLayout();
    QLabel *newUsernameLabel = new QLabel("Username/Email:", this);
    _inputNewUsername = new QLineEdit(this);

    usernameInputLayout->addWidget(newUsernameLabel);
    usernameInputLayout->addWidget(_inputNewUsername);

    QHBoxLayout * passwordInputLayout = new QHBoxLayout();
    QLabel *newPasswordLabel = new QLabel("Password:", this);
    _inputNewPassword = new QLineEdit(this);

    passwordInputLayout->addWidget(newPasswordLabel);
    passwordInputLayout->addWidget(_inputNewPassword);

    // Add layouts to input group
    inputLayout->addLayout(rowLayout);
    inputLayout->addLayout(nameInputLayout);
    inputLayout->addLayout(usernameInputLayout);
    inputLayout->addLayout(passwordInputLayout);

    // New button to transfer values to the display section
    QPushButton *transferValuesButton = new QPushButton("Transfer Values", this);
    inputLayout->addWidget(transferValuesButton);

    // Set fixed widths and styles for top section
    rowLabel->setFixedWidth(textLabelWidth);
    newNameLabel->setFixedWidth(textLabelWidth);
    newUsernameLabel->setFixedWidth(textLabelWidth);
    newPasswordLabel->setFixedWidth(textLabelWidth);

    rowLabel->setStyleSheet("font-size: 16px;");
    newNameLabel->setStyleSheet("font-size: 16px;");
    newUsernameLabel->setStyleSheet("font-size: 16px;");
    newPasswordLabel->setStyleSheet("font-size: 16px;");
    searchRowEditButton->setStyleSheet("font-size: 16px;");
    transferValuesButton->setStyleSheet("font-size: 16px;");

    _inputRowEdit->setFixedHeight(40);
    _inputNewName->setFixedHeight(40);
    _inputNewUsername->setFixedHeight(40);
    _inputNewPassword->setFixedHeight(40);
    searchRowEditButton->setFixedHeight(40);
    transferValuesButton->setFixedHeight(40);

    // Bottom section for displaying old and new values and save button
    QGroupBox * displayGroup = new QGroupBox("Old and New Values", this);
    displayGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 18px; }");
    QVBoxLayout * displayLayout = new QVBoxLayout(displayGroup);

    QHBoxLayout * oldNameLayout = new QHBoxLayout();
    QLabel *oldNameLabel = new QLabel("Old Name/Website:", this);
    _showOldName = new QLabel(this);
    QLabel *newNameDisplayLabel = new QLabel("New Name/Website:", this);
    _showNewName = new QLabel(this);

    oldNameLayout->addWidget(oldNameLabel);
    oldNameLayout->addWidget(_showOldName);
    oldNameLayout->addWidget(newNameDisplayLabel);
    oldNameLayout->addWidget(_showNewName);

    QHBoxLayout * oldUsernameLayout = new QHBoxLayout();
    QLabel *oldUsernameLabel = new QLabel("Old Username/Email:", this);
    _showOldUsername = new QLabel(this);
    QLabel *newUsernameDisplayLabel = new QLabel("New Username/Email:", this);
    _showNewUsername = new QLabel(this);

    oldUsernameLayout->addWidget(oldUsernameLabel);
    oldUsernameLayout->addWidget(_showOldUsername);
    oldUsernameLayout->addWidget(newUsernameDisplayLabel);
    oldUsernameLayout->addWidget(_showNewUsername);

    QHBoxLayout * oldPasswordLayout = new QHBoxLayout();
    QLabel *oldPasswordLabel = new QLabel("Old Password:", this);
    _showOldPassword = new QLabel(this);
    QLabel *newPasswordDisplayLabel = new QLabel("New Password:", this);
    _showNewPassword = new QLabel(this);

    oldPasswordLayout->addWidget(oldPasswordLabel);
    oldPasswordLayout->addWidget(_showOldPassword);
    oldPasswordLayout->addWidget(newPasswordDisplayLabel);
    oldPasswordLayout->addWidget(_showNewPassword);

    // Save changes button
    _saveChangesNormPasswordEdit = new QPushButton("Save Changes", this);
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(_saveChangesNormPasswordEdit);

    // Add layouts to display group
    displayLayout->addLayout(oldNameLayout);
    displayLayout->addLayout(oldUsernameLayout);
    displayLayout->addLayout(oldPasswordLayout);
    displayLayout->addLayout(buttonLayout);

    // Set fixed styles for bottom section
    _showOldName->setStyleSheet("font-size: 16px;");
    _showOldUsername->setStyleSheet("font-size: 16px;");
    _showOldPassword->setStyleSheet("font-size: 16px;");
    _showNewName->setStyleSheet("font-size: 16px;");
    _showNewUsername->setStyleSheet("font-size: 16px;");
    _showNewPassword->setStyleSheet("font-size: 16px;");
    _saveChangesNormPasswordEdit->setStyleSheet("font-size: 16px;");
    _saveChangesNormPasswordEdit->setFixedHeight(40);

    // Add groups to main layout
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(displayGroup);

    _centerNormPasswordEdit->setLayout(mainLayout);
    _centerNormPasswordEdit->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);
    _centerNormPasswordEdit->hide();

    // Connect signals and slots
    connect(searchRowEditButton, SIGNAL(clicked()), this, SLOT(searchRowEdit()));
    connect(_saveChangesNormPasswordEdit, SIGNAL(clicked()), this, SLOT(changePasswordEntry()));
    connect(transferValuesButton, SIGNAL(clicked()), this, SLOT(transferValues()));
}

void MainWindow::setupPasswordList() {
    _centerPasswordList = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(_centerPasswordList);

    QGroupBox *listGroup = new QGroupBox("Password List", this);
    QVBoxLayout *listLayout = new QVBoxLayout(listGroup);

    _scrollArea = new QScrollArea(this);
    QWidget *scrollWidget = new QWidget();
    _gridLayout = new QGridLayout(scrollWidget);

    scrollWidget->setLayout(_gridLayout);
    _scrollArea->setWidget(scrollWidget);
    _scrollArea->setWidgetResizable(true);
    _scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    listLayout->addWidget(_scrollArea);
    listGroup->setLayout(listLayout);

    mainLayout->addWidget(listGroup);
    _centerPasswordList->setLayout(mainLayout);
    _centerPasswordList->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);

    _centerPasswordList->hide();
}

void MainWindow::setupPasswordGen() {
    qDebug() << "Starting setupPasswordGen";

    // Initialisiere Checkboxen
    _allowLowAlphabet = new QCheckBox("Include Lowercase Alphabet (a-z)", this);
    _allowUpAlphabet = new QCheckBox("Include Uppercase Alphabet (A-Z)", this);
    _allowNumbers = new QCheckBox("Include Numbers (0-9)", this);
    _allowSymbols = new QCheckBox("Include Symbols", this);

    qDebug() << "Checkboxes initialized";

    // Setze Standardwerte für Checkboxen
    _allowLowAlphabet->setChecked(true);
    _allowUpAlphabet->setChecked(true);
    _allowNumbers->setChecked(true);
    _allowSymbols->setChecked(true);

    qDebug() << "Default values set";

    // Verbinde Checkboxen mit den entsprechenden Slots
    connect(_allowLowAlphabet, &QCheckBox::toggled, this, &MainWindow::onAllowLowAlphabetToggled);
    connect(_allowUpAlphabet, &QCheckBox::toggled, this, &MainWindow::onAllowUpAlphabetToggled);
    connect(_allowNumbers, &QCheckBox::toggled, this, &MainWindow::onAllowNumbersToggled);
    connect(_allowSymbols, &QCheckBox::toggled, this, &MainWindow::onAllowSymbolsToggled);

    qDebug() << "Connections established";

    // Erstelle das zentrale Widget und Layout
    _centerPasswordGen = new QWidget(this);
    QVBoxLayout * genLayout = new QVBoxLayout(_centerPasswordGen);
    genLayout->setSpacing(10);
    genLayout->setContentsMargins(20, 20, 20, 20);

    // Erstelle die Optionsgruppe
    QGroupBox * optionsGroup = new QGroupBox("Password Generation Options", this);
    QVBoxLayout * optionsLayout = new QVBoxLayout(optionsGroup);

    optionsLayout->addWidget(_allowLowAlphabet);
    optionsLayout->addWidget(_allowUpAlphabet);
    optionsLayout->addWidget(_allowNumbers);
    optionsLayout->addWidget(_allowSymbols);

    QLabel *allowedSymbolsLabel = new QLabel("Allowed Symbols:", this);
    _showAllowedSymbols = new QLineEdit(this);
    _showAllowedSymbols->setPlaceholderText("Enter your symbols");
    _showAllowedSymbols->setText("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
    optionsLayout->addWidget(allowedSymbolsLabel);
    optionsLayout->addWidget(_showAllowedSymbols);

    QLabel *passwordLengthLabel = new QLabel("Password Length:", this);
    _passwordLengthInput = new QLineEdit(this);
    _passwordLengthInput->setPlaceholderText("Enter password length (1-20)");
    _passwordLengthInput->setText("16");
    _passwordLengthInput->setValidator(new QIntValidator(1, 20, this));
    optionsLayout->addWidget(passwordLengthLabel);
    optionsLayout->addWidget(_passwordLengthInput);

    optionsGroup->setLayout(optionsLayout);
    genLayout->addWidget(optionsGroup);

    // Erstelle die Ausgabengruppe
    QGroupBox * outputGroup = new QGroupBox("Generated Password", this);
    QVBoxLayout * outputLayout = new QVBoxLayout(outputGroup);

    _passwordOutput = new QLineEdit(this);
    _passwordOutput->setReadOnly(true);
    _passwordOutput->setStyleSheet("background-color: #252526; color: #ffffff;");
    _passwordOutput->setAlignment(Qt::AlignCenter);
    _passwordOutput->setFixedHeight(30);
    outputLayout->addWidget(_passwordOutput);

    _startPasswordGen = new QPushButton("Generate Password", this);
    _startPasswordGen->setFixedHeight(40);
    connect(_startPasswordGen, &QPushButton::clicked, this, &MainWindow::startPasswordGen);
    outputLayout->addWidget(_startPasswordGen);

    outputGroup->setLayout(outputLayout);
    genLayout->addWidget(outputGroup);

    _centerPasswordGen->setLayout(genLayout);
    _centerPasswordGen->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);
    _centerPasswordGen->hide();

    qDebug() << "setupPasswordGen completed";
}

void MainWindow::setupLockscreen() {
    int widgetWidth = 200;
    int widgetHeight = 120;

    int buttonHeight = 30;

    _lockscreenWidget = new QWidget(this);
    _lockscreenLayout = new QVBoxLayout(_lockscreenWidget);
    _lockscreenWidget->setLayout(_lockscreenLayout);

    _inputField = new QLineEdit(_lockscreenWidget);
    _inputField->setFixedHeight(buttonHeight);

    _buttonConfirm = new QPushButton("Confirm", _lockscreenWidget);
    _buttonConfirm->setFixedHeight(buttonHeight);

    _lockscreenLayout->addWidget(_inputField);
    _lockscreenLayout->addWidget(_buttonConfirm);

    _lockscreenWidget->setGeometry(_middleWidthScreen - widgetWidth / 2, _middleHeightScreen - widgetHeight / 2,
                                   widgetWidth, widgetHeight);
    _lockscreenWidget->show();

    connect(_buttonConfirm, SIGNAL(clicked()), this, SLOT(ConfirmPassword()));
}

void MainWindow::setupEditMaster() {
    _centerMasterPasswordEdit = new QWidget(this);
    QVBoxLayout *editLayout = new QVBoxLayout(_centerMasterPasswordEdit);
    editLayout->setSpacing(10);
    editLayout->setContentsMargins(20, 20, 20, 20);

    QGroupBox *editGroup = new QGroupBox("Edit Master Password", this);
    QGridLayout *groupLayout = new QGridLayout(editGroup);

    _oldMasterPasswordLabel = new QLabel("Old Master Password:", this);
    _inputOldMasterPassword = new QLineEdit(this);

    _newMasterPasswordLabel = new QLabel("New Master Password:", this);
    _inputNewMasterPassword = new QLineEdit(this);

    _changeMasterPassword = new QPushButton("Change Master Password", this);

    groupLayout->addWidget(_oldMasterPasswordLabel, 0, 0);
    groupLayout->addWidget(_inputOldMasterPassword, 0, 1);
    groupLayout->addWidget(_newMasterPasswordLabel, 1, 0);
    groupLayout->addWidget(_inputNewMasterPassword, 1, 1);
    groupLayout->addWidget(_changeMasterPassword, 2, 0, 1, 2);

    groupLayout->setColumnStretch(1, 1); // Ensures that the QLineEdit widgets expand

    editGroup->setLayout(groupLayout);
    editLayout->addWidget(editGroup);
    editLayout->addStretch(); // Adds a stretch to take up remaining space

    _centerMasterPasswordEdit->setLayout(editLayout);
    _centerMasterPasswordEdit->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);
    _centerMasterPasswordEdit->hide();

    connect(_changeMasterPassword, SIGNAL(clicked()), this, SLOT(checkChangeMasterPassword()));
}

void MainWindow::setupPasswordDel() {
    int textLabelWidth = 130;

    _centerPasswordDel = new QWidget(this);
    QVBoxLayout * mainLayout = new QVBoxLayout(_centerPasswordDel);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Top section for input and search/delete buttons
    QGroupBox * inputGroup = new QGroupBox("Delete Password Entry", this);
    inputGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 18px; }");
    QVBoxLayout * inputLayout = new QVBoxLayout(inputGroup);

    // Row number input and buttons
    QHBoxLayout * rowLayout = new QHBoxLayout();
    QLabel *rowLabel = new QLabel("Row Number:", this);
    _inputRowDel = new QLineEdit(this);
    QPushButton *searchRowEditButton = new QPushButton("Search", this);
    QPushButton *deleteRowButton = new QPushButton("Delete", this);

    rowLayout->addWidget(rowLabel);
    rowLayout->addWidget(_inputRowDel);
    rowLayout->addWidget(searchRowEditButton);
    rowLayout->addWidget(deleteRowButton);

    // Set fixed widths and styles for row input
    rowLabel->setFixedWidth(textLabelWidth);
    rowLabel->setStyleSheet("font-size: 16px;");
    searchRowEditButton->setStyleSheet("font-size: 16px;");
    deleteRowButton->setStyleSheet("font-size: 16px;");
    _inputRowDel->setFixedHeight(40);
    searchRowEditButton->setFixedHeight(40);
    deleteRowButton->setFixedHeight(40);

    // Labels to display old values
    QLabel *oldNameLabel = new QLabel("Name/Website:", this);
    _showOldNameDel = new QLabel(this);

    QLabel *oldUsernameLabel = new QLabel("Username/Email:", this);
    _showOldUsernameDel = new QLabel(this);

    QLabel *oldPasswordLabel = new QLabel("Password:", this);
    _showOldPasswordDel = new QLabel(this);

    // Set styles for old value labels
    oldNameLabel->setStyleSheet("font-size: 16px;");
    oldUsernameLabel->setStyleSheet("font-size: 16px;");
    oldPasswordLabel->setStyleSheet("font-size: 16px;");

    // Add labels to a vertical layout
    QVBoxLayout * labelsLayout = new QVBoxLayout();
    labelsLayout->addWidget(oldNameLabel);
    labelsLayout->addWidget(_showOldNameDel);
    labelsLayout->addWidget(oldUsernameLabel);
    labelsLayout->addWidget(_showOldUsernameDel);
    labelsLayout->addWidget(oldPasswordLabel);
    labelsLayout->addWidget(_showOldPasswordDel);

    // Add row input and labels layout to input group
    inputLayout->addLayout(rowLayout);
    inputLayout->addSpacing(20); // Add some spacing between row input and labels
    inputLayout->addLayout(labelsLayout);

    // Add delete button aligned to the right
    QHBoxLayout * deleteButtonLayout = new QHBoxLayout();
    deleteButtonLayout->addStretch(); // Add stretch to push button to the right
    deleteButtonLayout->addWidget(deleteRowButton);

    // Add delete button layout to input group
    inputLayout->addLayout(deleteButtonLayout);

    // Add input group to main layout
    mainLayout->addWidget(inputGroup);

    _centerPasswordDel->setLayout(mainLayout);
    _centerPasswordDel->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);
    _centerPasswordDel->hide();

    // Connect signals and slots
    connect(searchRowEditButton, SIGNAL(clicked()), this, SLOT(searchRowDel()));
    connect(deleteRowButton, SIGNAL(clicked()), this, SLOT(deletePasswordEntry()));
}

void MainWindow::setupAddPassword() {
    int textLabelWidth = 130;

    _centerAddPassword = new QWidget(this);
    QVBoxLayout * mainLayout = new QVBoxLayout(_centerAddPassword);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Top section for input
    QGroupBox * inputGroup = new QGroupBox("Add Password Entry", this);
    inputGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 18px; }");
    QVBoxLayout * inputLayout = new QVBoxLayout(inputGroup);

    // New name, username, and password inputs
    QHBoxLayout * nameInputLayout = new QHBoxLayout();
    QLabel *newNameLabel = new QLabel("Name/Website:", this);
    _inputAddName = new QLineEdit(this);

    nameInputLayout->addWidget(newNameLabel);
    nameInputLayout->addWidget(_inputAddName);

    QHBoxLayout * usernameInputLayout = new QHBoxLayout();
    QLabel *newUsernameLabel = new QLabel("Username/Email:", this);
    _inputAddUsername = new QLineEdit(this);

    usernameInputLayout->addWidget(newUsernameLabel);
    usernameInputLayout->addWidget(_inputAddUsername);

    QHBoxLayout * passwordInputLayout = new QHBoxLayout();
    QLabel *newPasswordLabel = new QLabel("Password:", this);
    _inputAddPassword = new QLineEdit(this);

    passwordInputLayout->addWidget(newPasswordLabel);
    passwordInputLayout->addWidget(_inputAddPassword);

    // Add layouts to input group
    inputLayout->addLayout(nameInputLayout);
    inputLayout->addLayout(usernameInputLayout);
    inputLayout->addLayout(passwordInputLayout);

    // Set fixed widths and styles for input section
    newNameLabel->setFixedWidth(textLabelWidth);
    newUsernameLabel->setFixedWidth(textLabelWidth);
    newPasswordLabel->setFixedWidth(textLabelWidth);

    newNameLabel->setStyleSheet("font-size: 16px;");
    newUsernameLabel->setStyleSheet("font-size: 16px;");
    newPasswordLabel->setStyleSheet("font-size: 16px;");

    _inputAddName->setFixedHeight(40);
    _inputAddUsername->setFixedHeight(40);
    _inputAddPassword->setFixedHeight(40);

    // Bottom section for displaying new values and save button
    QGroupBox * displayGroup = new QGroupBox("New Values", this);
    displayGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 18px; }");
    QVBoxLayout * displayLayout = new QVBoxLayout(displayGroup);

    QHBoxLayout * newNameLayout = new QHBoxLayout();
    QLabel *newNameDisplayLabel = new QLabel("New Name/Website:", this);
    _showAddName = new QLabel(this);

    newNameLayout->addWidget(newNameDisplayLabel);
    newNameLayout->addWidget(_showAddName);

    QHBoxLayout * newUsernameLayout = new QHBoxLayout();
    QLabel *newUsernameDisplayLabel = new QLabel("New Username/Email:", this);
    _showAddUsername = new QLabel(this);

    newUsernameLayout->addWidget(newUsernameDisplayLabel);
    newUsernameLayout->addWidget(_showAddUsername);

    QHBoxLayout * newPasswordLayout = new QHBoxLayout();
    QLabel *newPasswordDisplayLabel = new QLabel("New Password:", this);
    _showAddPassword = new QLabel(this);

    newPasswordLayout->addWidget(newPasswordDisplayLabel);
    newPasswordLayout->addWidget(_showAddPassword);

    // Save new entry button
    _saveNewPasswordButton = new QPushButton("Save Entry", this);
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(_saveNewPasswordButton);

    // Add layouts to display group
    displayLayout->addLayout(newNameLayout);
    displayLayout->addLayout(newUsernameLayout);
    displayLayout->addLayout(newPasswordLayout);
    displayLayout->addLayout(buttonLayout);

    // Set fixed styles for display section
    _showAddName->setStyleSheet("font-size: 16px;");
    _showAddUsername->setStyleSheet("font-size: 16px;");
    _showAddPassword->setStyleSheet("font-size: 16px;");
    _saveNewPasswordButton->setStyleSheet("font-size: 16px;");
    _saveNewPasswordButton->setFixedHeight(40);

    // Add groups to main layout
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(displayGroup);

    _centerAddPassword->setLayout(mainLayout);
    _centerAddPassword->setGeometry(210, 100, _screenWidth - 210, _screenHeight - 100);
    _centerAddPassword->hide();

    // Connect signals and slots
    connect(_inputAddName, &QLineEdit::textChanged, _showAddName, &QLabel::setText);
    connect(_inputAddUsername, &QLineEdit::textChanged, _showAddUsername, &QLabel::setText);
    connect(_inputAddPassword, &QLineEdit::textChanged, _showAddPassword, &QLabel::setText);
    connect(_saveNewPasswordButton, &QPushButton::clicked, this, &MainWindow::addPasswordEntry);
}
