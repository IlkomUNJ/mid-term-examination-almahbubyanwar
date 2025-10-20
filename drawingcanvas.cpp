#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    isPaintLinesClicked = false;
    detectIntersectSegments = false;
    m_points.clear();
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    /* Todo
     * Implement lines drawing per even pair
    */

    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection(){
    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "image width " << image.width() << endl;
    cout << "image height " << image.height() << endl;

    //To not crash we set initial size of the matrix

    vector<CustomMatrix> windows(image.width()*image.height());

    // Get the pixel value as an ARGB integer (QRgb is a typedef for unsigned int)

    for(int i = 1; i < image.width()-1;i++){
        for(int j = 1; j < image.height()-1;j++){
            bool local_window[3][3] = {false};

            for(int m=-1;m<=1;m++){
                for(int n=-1;n<=1;n++){
                    QRgb rgbValue = image.pixel(i+m, j+n);
                    local_window[m+1][n+1] = (rgbValue != 0xffffffff);
                }
            }

            CustomMatrix mat(local_window);

            windows.push_back(mat);
        }
    }
    return;
}

// void DrawingCanvas::segmentDetection() {
//     // isPaintLinesClicked = true;
//     detectIntersectSegments = true;
//     detect_gridsize = 6;
// }

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4); // 4-pixel wide line
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        // Set the painter's pen to our custom pen.
        painter.setPen(pen);

        for(int i=0;i<m_points.size()-1;i+=2){
            //cout << m_points[i].x() << endl;
            painter.drawLine(m_points[i], m_points[i+1]);
        }
        // isPaintLinesClicked = false;

        //return painter pen to blue
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }

    if (detectIntersectSegments) {
        QPair<int,int> cellSize = QPair<int, int>(floor(WINDOW_WIDTH/detect_gridsize), floor(WINDOW_HEIGHT/detect_gridsize));
        // first, we draw the grids for clarity.
        QPen pen(Qt::green, 1);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        QVector<QVector<QRect>> grid;
        for (int i = 0; i < detect_gridsize; ++i) {
            QVector<QRect> gridRow;
            for (int j = 0; j < detect_gridsize; ++j) {
                QRect rect = QRect(i * cellSize.first, j*cellSize.second, 
                cellSize.first, cellSize.second);
                painter.drawRect(rect);
                gridRow.append(rect);
            }
            grid.append(gridRow);
        };
        // second, we make vectors for pointPairs that essentially create a line segment.
        QVector<QPair<QPoint&, QPoint&> > lineSegments;
        for (int i = 0; i < m_points.length() - 1; i = i + 2) {
            // obviously, we don't consider 
            lineSegments.append(QPair<QPoint&, QPoint&>(m_points[i], m_points[i+1]));
            QPen segmentPen(Qt::darkGreen, 2);
            painter.setPen(segmentPen);
            painter.drawLine(m_points[i], m_points[i+1]);
        }
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    isPaintLinesClicked = false;
    detectIntersectSegments = false;
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}


