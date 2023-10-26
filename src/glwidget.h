#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/glu.h>


class GLWidget: public QOpenGLWidget {
  Q_OBJECT

public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();

  enum VerticesDisplayMethod {
      SQUARE,
      CIRCLE
  };

  enum EdgesType {
      SOLID,
      DASHED
  };

  QString modelPath;

  QColor get_background() { return background; }
  GLfloat get_width() { return line_width; }
  EdgesType get_edges_type() { return edges_type; }
  QColor get_edges_color() { return edges_color; }
  VerticesDisplayMethod get_vetr_method() { return vetr_method; }
  GLfloat get_vertices_size() { return vertices_size; }
  QColor get_vertices_color() { return vertices_color; }

  void set_background(QColor color) { background = color; }

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void rotation(double angle, double*, double*);
  void set_vertices_color(QColor new_color);
  void set_edges_color(QColor new_color);



private:
  void drawStar(float fX, float fY);
  void drawStars();
  void drawStripes();
  void drawAxis();

  QColor background;
  GLfloat line_width = 1.0;
  GLfloat vertices_size = 5.0;
  QColor vertices_color = Qt::white;
  QColor edges_color = Qt::white;
  EdgesType edges_type = EdgesType::SOLID;

  double prev_angle_x = 0;
  double prev_angle_y = 0;
  double prev_angle_z = 0;
  double current_angle_x = 0.0;
  double current_angle_y = 0.0;
  double current_angle_z = 0.0;
  double scale = 1.0;
  double position_x = 0;
  double position_y = 0;
  double position_z = 0;



  VerticesDisplayMethod vetr_method = VerticesDisplayMethod::SQUARE;


  const static GLint coords_size = 8;
  // (должен заполнять парсер)
  GLfloat cubeCoords[coords_size][3];
  GLfloat currentCubeCoords[coords_size][3];
  GLint cubeLines[12][2];

public slots:
  void set_position_x(double);
  void set_position_y(double);
  void set_position_z(double);
  void rotation_x(double angle);
  void rotation_y(double angle);
  void rotation_z(double angle);
  void set_vertices_size(int);
  void set_vertices_method(int);
  void set_edges_type(int);
  void set_line_width(int);
  void set_scale(int size);


};
#endif // GLWIDGET_H
