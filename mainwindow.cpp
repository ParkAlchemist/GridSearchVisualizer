#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene_ = new QGraphicsScene(this);

    cv_ = new CustomView();
    this->layout()->addWidget(cv_);
    cv_->setGeometry(left_margin, top_margin,
                    window_width + 2, window_heigth + 2); // +2 because borders are 1 pixel wide)
    cv_->setScene(scene_);
    cv_->setInteractive(true);
    cv_->setMouseTracking(true);

    init();
}

MainWindow::~MainWindow()
{
    cv_->scene()->clear();
    delete grid_;
    delete timer_;
    delete stall_timer_;
    delete stall_loop_;
    delete alg_;
    delete ui;
}

void MainWindow::set_start(int x, int y)
{
    grid_->set_start(x,y);

    SquareNode* item =  nodes_.at(y).at(x);
    item->setBrush(QBrush(Qt::green));
}

void MainWindow::set_goal(int x, int y)
{
    grid_->set_goal(x,y);

    SquareNode* item =  nodes_.at(y).at(x);
    item->setBrush(Qt::red);
}

void MainWindow::drawPath(std::vector<Node *> path)
{
    for(Node* n : path){
        if(n->state != State::Start && n->state != State::Goal){

            stall_timer_->start();
            stall_loop_->exec();

            SquareNode* item =  nodes_.at(n->y).at(n->x);
            item->setBrush(QBrush(Qt::magenta));
        }
    }
}

void MainWindow::drawLine(QLineF line)
{
    stall_timer_->start();
    stall_loop_->exec();

    QPen p(Qt::GlobalColor::cyan);
    p.setWidth(3);
    QGraphicsLineItem * l = scene_->addLine(line, p);
    lines_.push_back(l);
}

void MainWindow::pathSmoothing()
{

    int start = 0;
    int end = 2;

    ps_path_.push_back(path_[start]);

    while(start < (int)path_.size() - 2 && end <= (int)path_.size() - 1){

        // calculate area for line of sight
        int start_x = path_[start]->x;
        int start_y = path_[start]->y;

        int end_x = path_[end]->x;
        int end_y = path_[end]->y;

        int left = std::min(start_x, end_x);
        int right = std::max(start_x, end_x);
        int bottom = std::min(start_y, end_y);
        int top = std::max(start_y, end_y);

        bool los = true;

        // check line of sight
        for(int y = bottom; y <= top; ++y){

            if(!los) break;

            for(int x = left; x <= right; ++x){

                Node* n = grid_->get()->at(y).at(x);
                if(n->state == State::Obstacle){

                    float center_x = n->x;
                    float center_y = n->y;

                    float dist_from_upper_line = distancePtL(start_x, start_y+0.5, end_x, end_y+0.5, center_x, center_y);
                    float dist_from_lower_line = distancePtL(start_x, start_y-0.5, end_x, end_y-0.5, center_x, center_y);

                    if(dist_from_lower_line < 0.9 && dist_from_upper_line < 0.9){
                        los = false;
                        break;
                    }
                }
            }
        }

        if(los){
            //search_update(path_[end-1]->x, path_[end-1]->y, Qt::lightGray);
            end++;
        }
        else{
            // call painting event to draw line to represent jump
            QLineF line(path_[start]->x*node_width_ + node_width_/2, path_[start]->y*node_heigth_ + node_heigth_/2,
                        path_[end-1]->x*node_width_ + node_width_/2, path_[end-1]->y*node_heigth_ + node_heigth_/2);
            drawLine(line);

            //search_update(path_[end-1]->x, path_[end-1]->y, Qt::darkCyan);

            if(start != 0) ps_path_.push_back(path_[start]);

            start = end - 1;
            end = start + 2;
        }
    }
    QLineF line(path_[start]->x*node_width_ + node_width_/2, path_[start]->y*node_heigth_ + node_heigth_/2,
                path_[end-1]->x*node_width_ + node_width_/2, path_[end-1]->y*node_heigth_ + node_heigth_/2);
    drawLine(line);
    ps_path_.push_back(path_[end-1]);
}

void MainWindow::newPathSmoothing()
{
    int start = 0;
    int end = path_.size()-1;

    ps_path_.push_back(path_[start]);

    while(start < (int)path_.size() - 2){

        // calculate area for line of sight
        int start_x = path_[start]->x;
        int start_y = path_[start]->y;

        int end_x = path_[end]->x;
        int end_y = path_[end]->y;

        int left = std::min(start_x, end_x);
        int right = std::max(start_x, end_x);
        int bottom = std::min(start_y, end_y);
        int top = std::max(start_y, end_y);

        bool los = true;

        // check line of sight
        for(int y = bottom; y <= top; ++y){

            if(!los) break;

            for(int x = left; x <= right; ++x){

                Node* n = grid_->get()->at(y).at(x);
                if(n->state == State::Obstacle){

                    if(intersectsNode(start_x+0.5, start_y+0.5, end_x+0.5, end_y+0.5, n->x, n->y, grid_->get())){
                        los = false;
                        break;
                    }
                }
            }
        }

        if(!los){
            end--;
        }
        else{
            QLineF line(path_[start]->x*node_width_ + node_width_/2, path_[start]->y*node_heigth_ + node_heigth_/2,
                        path_[end]->x*node_width_ + node_width_/2, path_[end]->y*node_heigth_ + node_heigth_/2);
            drawLine(line);

            //search_update(path_[end]->x, path_[end]->y, Qt::darkCyan);

            if(start != 0) ps_path_.push_back(path_[start]);

            start = end;
            end = path_.size()-1;
        }
    }

    if(start != end){
        QLineF line(path_[start]->x*node_width_ + node_width_/2, path_[start]->y*node_heigth_ + node_heigth_/2,
                    path_[end]->x*node_width_ + node_width_/2, path_[end]->y*node_heigth_ + node_heigth_/2);
        drawLine(line);
    }

    ps_path_.push_back(path_[end]);
}

void MainWindow::tick()
{
    time_ = time_.addMSecs(100);
    QString t = time_.toString("mm:ss:z");
    ui->lcdNumber->display(t);
}

// triggered by mouse events
void MainWindow::change_color(int x, int y, Qt::GlobalColor color)
{
    x = x/node_width_;
    y = y/node_heigth_;

    SquareNode* item =  nodes_.at(y).at(x);
    Node* n = grid_->get()->at(y).at(x);

    if(color == Qt::black){
        if(n->state == State::Free){
            n->state = State::Obstacle;
            item->setBrush(QBrush(Qt::black));
        }
        return;
    }
    if(color == Qt::white){
        if(n->state == State::Obstacle){
            n->state = State::Free;
            item->setBrush(QBrush(Qt::white));
        }
        return;
    }
    if(color == Qt::green){

        SquareNode* s = nodes_.at(grid_->get_start()->y).at(grid_->get_start()->x);
        s->setBrush(QBrush(Qt::white));
        set_start(n->x, n->y);
        return;
    }
    if(color == Qt::red){

        SquareNode* g = nodes_.at(grid_->get_goal()->y).at(grid_->get_goal()->x);
        g->setBrush(QBrush(Qt::white));
        set_goal(n->x, n->y);
        return;
    }
    return;
}

// called during search
void MainWindow::search_update(int x, int y, Qt::GlobalColor color)
{
    // stall
    stall_timer_->start();
    stall_loop_->exec();

    nodes_.at(y).at(x)->setBrush(QBrush(color));
}

void MainWindow::init()
{
    // initialize timer
    timer_ = new QTimer();
    timer_->setTimerType(Qt::PreciseTimer);
    timer_->setSingleShot(false);
    timer_->setInterval(100);
    QObject::connect(timer_, &QTimer::timeout, this, &MainWindow::tick);
    ui->lcdNumber->display("00:00:0");

    time_.setHMS(0,0,0,0); 

    // init stall
    stall_timer_ = new QTimer();
    stall_timer_->setInterval(stall_time_);
    stall_loop_ = new QEventLoop();

    QObject::connect(stall_timer_, SIGNAL(timeout()), stall_loop_, SLOT(quit()));

    // hide elements
    for(auto button : ui->heuristicRadioButtons->buttons()){
        button->setEnabled(false);
        button->setHidden(true);
    }
    ui->heurLabel->setHidden(true);

    //radio buttons
    QObject::connect(ui->heuristicRadioButtons, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(set_Heuristic(QAbstractButton*)));

    //info
    ui->InfoLabel->setText("");
    ui->textBrowser->setText("");
    QFont f("Arial", 20, QFont::Bold);
    ui->InfoLabel->setFont(f);
    ui->textBrowser->setReadOnly(true);
}

void MainWindow::setInfoLabel()
{
    std::string info_text = "Grid Size: " + std::to_string(grid_width_) + "x" + std::to_string(grid_heigth_);
    info_text += " Neighbours: " + std::to_string(neighbours_);
    ui->InfoLabel->setText(QString::fromStdString(info_text));
}

void MainWindow::showInfo()
{
    std::string node_info = "Nodes Expanded: ";
    std::string path_info = "Path Lenght: ";
    std::string ps_info = "Path Lenght After Smoothing: ";

    int expanded_nodes = 0;
    float path_length = 0;
    float psPath_length = 0;

    // calc amount of expanded nodes
    for(int y = 0; y < grid_heigth_; ++y){
        for(int x = 0; x < grid_width_; ++x){
            if(grid_->get()->at(y).at(x)->gray || grid_->get()->at(y).at(x)->black){
                expanded_nodes++;
            }
        }
    }

    // calc original path length
    for(int n = 1; n < (int)path_.size(); ++n){
        path_length += distance(path_[n-1], path_[n]);
    }

    // calc ps path length
    for(int k = 1; k < (int)ps_path_.size(); ++k){
        psPath_length += distance(ps_path_[k-1], ps_path_[k]);
    }

    node_info += std::to_string(expanded_nodes) + "\n";

    if(path_length == 0){
        path_info = "No Path Found \n";
    }
    else{
        path_info += precision(path_length, 2) + "\n";
    }

    if(psPath_length == 0){
        ps_info = "";
    }
    else{
        ps_info += precision(psPath_length, 2);
    }

    ui->textBrowser->setText(QString::fromStdString(node_info + path_info + ps_info));
}

void MainWindow::draw_grid()
{
    scene_->clear();
    nodes_.clear();

    node_width_ = window_width/grid_width_;
    node_heigth_ = window_heigth/grid_heigth_;

    for(int j = 0; j < grid_heigth_; ++j){
        std::vector<SquareNode*> node_vec;
        for(int i = 0; i < grid_width_; ++i){

            QRectF rect_(i*node_width_, j*node_heigth_, node_width_-1, node_heigth_-1); // compensate for added width and heigth from the pen
            SquareNode* n_ = new SquareNode(rect_);

            QObject::connect(n_, SIGNAL(change(int,int,Qt::GlobalColor)), this, SLOT(change_color(int,int,Qt::GlobalColor)));

            scene_->addItem(n_);

            n_->setBrush(QBrush(Qt::white));
            node_vec.push_back(n_);
        }
        nodes_.push_back(node_vec);
    }

    set_start(1, grid_heigth_/2); // default start
    set_goal(grid_width_-2, grid_heigth_/2); // default goal
}

void MainWindow::on_action32x16_triggered()
{   
    if(grid_width_ == 32 && grid_heigth_ == 16){

        return;
    }

    on_ClearButton_clicked();

    grid_width_ = 32;
    grid_heigth_ = 16;
    stall_time_ = 10;
    stall_timer_->setInterval(stall_time_);

    grid_ = new GridGraph(grid_width_, grid_heigth_);

    draw_grid();
    setInfoLabel();
}

void MainWindow::on_action64x32_triggered()
{   
    if(grid_width_ == 64 && grid_heigth_ == 32){

        return;
    }

    on_ClearButton_clicked();

    grid_width_ = 64;
    grid_heigth_ = 32;
    stall_time_ = 5;
    stall_timer_->setInterval(stall_time_);

    grid_ = new GridGraph(grid_width_, grid_heigth_);

    draw_grid();
    setInfoLabel();
}

void MainWindow::on_action128x64_triggered()
{

    if(grid_width_ == 128 && grid_heigth_ == 64){

        return;
    }

    on_ClearButton_clicked();

    grid_width_ = 128;
    grid_heigth_ = 64;
    stall_time_ = 1;
    stall_timer_->setInterval(stall_time_);

    grid_ = new GridGraph(grid_width_, grid_heigth_);

    draw_grid();
    setInfoLabel();
}

void MainWindow::on_action4_Neighbours_triggered()
{
    neighbours_ = 4;
    setInfoLabel();
}

void MainWindow::on_action8_Neighbours_triggered()
{
   neighbours_ = 8;
   setInfoLabel();
}

void MainWindow::on_RunButton_clicked()
{
    //set correct algortihm
    switch(ui->AlgcomboBox->currentIndex()){

        case Algorithm::DFS :
            alg_ = new SearchDFS();
            break;
        case Algorithm::BFS :
            alg_ = new SearchBFS();
            break;
        case Algorithm::Dijkstra :
            alg_ = new SearchDijkstra();
            break;
        case Algorithm::A_star :
            if(heuristic_ == Heuristic::H_none) return;
            alg_ = new SearchAStar(heuristic_);
            break;
        case Algorithm::GBFS :
            if(heuristic_ == Heuristic::H_none) return;
            alg_ = new SearchGBFS(heuristic_);
            break;
        default :
            alg_ = nullptr;
            break;
    }
    if(alg_ == nullptr) return;

    // disable mouse interactivity during search
    cv_->setEnabled(false);

    // clear text box
    ui->textBrowser->clear();

    QObject::connect(alg_, SIGNAL(change(int,int,Qt::GlobalColor)), this, SLOT(search_update(int,int,Qt::GlobalColor)));

    ui->lcdNumber->display("00:00:0");
    time_.setHMS(0,0,0,0);

    // reset grid
    grid_->init();
    grid_->setNeighbours(neighbours_);
    path_.clear();
    ps_path_.clear();

    //start search
    timer_->start();
    alg_->start(grid_->get_start(), grid_->get_goal());
    timer_->stop();

    path_ = alg_->getPath();

    if(!path_.empty()){
        drawPath(path_);
        std::reverse(path_.begin(), path_.end());
    }

    showInfo();
}


void MainWindow::on_CleanButton_clicked()
{
    if(!lines_.empty()){
        for(auto l : lines_){
            scene_->removeItem(l);
        }
        lines_.clear();
    }

    if(grid_ == nullptr){
        return;
    }
    for(int y = 0; y < grid_heigth_; ++y){
        for(int x = 0; x < grid_width_; ++x){
            Node* n = grid_->get()->at(y).at(x);
            if(n->state == State::Free){
                nodes_.at(y).at(x)->setBrush(QBrush(Qt::white));
            }
        }
    }

    path_.clear();
    ps_path_.clear();

    // enable mouse
    cv_->setEnabled(true);
}

void MainWindow::on_ClearButton_clicked()
{
    if(!lines_.empty()){
        for(auto l : lines_){
            scene_->removeItem(l);
        }
        lines_.clear();
    }

    if(grid_ == nullptr){
        return;
    }
    for(int y = 0; y < grid_heigth_; ++y){
        for(int x = 0; x < grid_width_; ++x){
            Node* n = grid_->get()->at(y).at(x);
            if(n->state != State::Goal && n->state != State::Start){
                n->state = State::Free;
                nodes_.at(y).at(x)->setBrush(QBrush(Qt::white));
            }
        }
    }

    path_.clear();
    ps_path_.clear();

    // enable mouse
    cv_->setEnabled(true);
}


void MainWindow::on_AlgcomboBox_currentIndexChanged(int index)
{
    if(index == Algorithm::A_star || index == Algorithm::GBFS){
        for(auto button : ui->heuristicRadioButtons->buttons() ){
            button->setEnabled(true);
            button->setHidden(false);
        }
        ui->heurLabel->setHidden(false);
        return;
    }
    for(auto button : ui->heuristicRadioButtons->buttons() ){
        button->setEnabled(false);
        button->setHidden(true);
    }
    ui->heurLabel->setHidden(true);
    return;
}

void MainWindow::set_Heuristic(QAbstractButton *b)
{
    qDebug() << "Selected:" << b->text();

    if(b->text() == "Manhattan"){
        heuristic_ = Heuristic::Manhattan;
    }
    else if(b->text() == "Octal"){
        heuristic_ = Heuristic::Octal;
    }
    else if(b->text() == "Euclidian"){
        heuristic_ = Heuristic::Euclidian;
    }
    else if(b->text() == "Chebyshev"){
        heuristic_ = Heuristic::Chebyshev;
    }
}

void MainWindow::on_smoothButton_clicked()
{
    if(!lines_.empty()){
        for(QGraphicsLineItem* l : lines_){
            scene_->removeItem(l);
        }
        lines_.clear();
        ps_path_.clear();
    }
    if(ui->smoothingV1But->isChecked() && path_.size() != 0){
        pathSmoothing();
        showInfo();
    }
    if(ui->smoothingV2But->isChecked() && path_.size() != 0){
        newPathSmoothing();
        showInfo();
    }
}

