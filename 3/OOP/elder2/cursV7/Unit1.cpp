//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
  HDC dc;
  tSun sn;
  tScene scene;
  tPlanet merc,venu,eart,mar,jup,sat,uran,nept,star;
//---------------------------------------------------------------------------
GLvoid tSun::sunInit(GLfloat _r, GLfloat _g, GLfloat _b, GLdouble _radius,
                             GLint _slices, GLint _stacks)
{
   r=_r; g=_g; b=_b; rad=_radius; slices=_slices; stacks=_stacks;
}

GLvoid tSun::creatSun(){
  glNewList(1,GL_COMPILE);
     obj=gluNewQuadric();
     glColor3f(r,g,b);
     gluQuadricDrawStyle(obj,GLU_LINE);
     gluSphere(obj, rad,slices,stacks);
  glEndList();
}
//---------------------------------------------------------------------------
GLvoid tPlanet::planetInit(GLfloat _r, GLfloat _g, GLfloat _b, GLdouble _radius,
                        GLint _slices,GLint _stacks, GLfloat _x,
                        GLfloat _y, GLfloat _z, GLint _number, GLfloat latitude)
{
 r=_r; g=_g; b=_b; rad=_radius; slices=_slices;
 stacks=_stacks; x=_x; y=_y; z=_z; number=_number;
}

GLvoid tPlanet::creatPlanet(){
  if(number==10){
    glNewList(number,GL_COMPILE);
       obj=gluNewQuadric();
       glColor3f(r,g,b);
       gluQuadricDrawStyle(obj,GLU_POINT);
       gluSphere(obj, rad,slices,stacks);
    glEndList();
  }
  else{
     glNewList(number,GL_COMPILE);
       obj=gluNewQuadric();
       glColor3f(r,g,b);
       gluQuadricDrawStyle(obj,GLU_LINE);
       gluSphere(obj, rad,slices,stacks);
     glEndList();
  }
}

GLvoid tPlanet::DrawPlanet(){
  glPushMatrix();
  polarView(0.0, 10, latitude, longitude);
  glTranslated(x, y, z);
  glCallList(number);
  glPopMatrix();

}
//---------------------------------------------------------------------------
GLvoid tScene::SceneInit(){

  sn.sunInit(1.0,1.0,0.0,0.3,20,20);
  sn.creatSun();
  merc.planetInit(0.5,1.0,0.2,0.1,20,20,0.6, 0.3, 0.0,2,10);
  merc.creatPlanet();
  venu.planetInit(0.5,0.2,0.3,0.16,20,20,0.9, 1.1, 0.0,3,1);
  venu.creatPlanet();
  eart.planetInit(0.3,0.6,0.7,0.17,20,20,1.3, 2.7, 0.0,4,10);
  eart.creatPlanet();
  mar.planetInit(1.0,0.0,0.0,0.19,20,20,1.7, 1.5, 0.0,5,0);
  mar.creatPlanet();
  jup.planetInit(0.2,4.0,0.9,0.3,20,20,1.9, 0.0, 0.0,6,7);
  jup.creatPlanet();
  sat.planetInit(0.4,0.1,0.1,0.21,20,20,2.2, 0.5, 0.0,7,0);
  sat.creatPlanet();
  uran.planetInit(0.7,1.0,0.5,0.25,20,20,2.5, 0.9, 0.0,8,12);
  uran.creatPlanet();
  nept.planetInit(0.3,0.3,0.8,0.11,20,20,3, 0.0, 0.0,9,0);
  nept.creatPlanet();
  star.planetInit(1.0,1.0,1.0,7,20,10,3, 0.0, 0.0,10,10);
  star.creatPlanet();

  radius =7;
  longinc = 0.2;
}

GLvoid tScene::polarView(GLdouble radius, GLdouble twist, GLdouble latitude,
                GLdouble longitude)
{
  glTranslated(0.0, 0.0, -radius);
  glRotated(-twist, 0.0, 0.0, 1.0);
  glRotated(-latitude, 1.0, 0.0, 0.0);
  glRotated(longitude, 0.0, 0.0, 1.0);
}

GLvoid tScene::DrawScene(){
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glPushMatrix();
  longitude+=longinc;
  polarView(radius, 10, 85, longitude);

  glCallList(1);

  nept.DrawPlanet();
  polarView(0, 10, 1, longitude-0.5);
  uran.DrawPlanet();
  polarView(0, 10, 1, longitude-0.5);
  sat.DrawPlanet();
  polarView(0, 10, 1, longitude-0.5);
  jup.DrawPlanet();
  polarView(0, 10, 1, longitude-0.5);
  mar.DrawPlanet();
  polarView(0, 10, 1, longitude-0.5);
  eart.DrawPlanet();
  polarView(0, 10, 1, longitude-0.5);
  venu.DrawPlanet();
  polarView(0, 10, 1, longitude-0.5);
  merc.DrawPlanet();
  polarView(0, 10, 1, longitude-0.5);
  star.DrawPlanet();
  glPopMatrix();
  SwapBuffers(dc);
}
//---------------------------------------------------------------------------

BOOL bSetupPixelFormat(HDC hdc){
  PIXELFORMATDESCRIPTOR pfd, *ppfd;
  int pixelformat;

  ppfd = &pfd;
  ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
  ppfd->nVersion = 1;
  ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  ppfd->dwLayerMask = PFD_MAIN_PLANE;
  ppfd->iPixelType = PFD_TYPE_COLORINDEX;
  ppfd->cColorBits = 8;
  ppfd->cDepthBits = 16;
  ppfd->cAccumBits = 0;
  ppfd->cStencilBits = 0;
  if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 ){
    return FALSE;
  }
  if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE){
    return FALSE;
  }
  return TRUE;
}

GLvoid TForm1::initGL(GLsizei width, GLsizei height){
  GLfloat aspect;
  glClearColor(0.0,0.0,0.0,0.0);
  glClearDepth( 1.0 );
  glEnable(GL_DEPTH_TEST);
  glMatrixMode( GL_PROJECTION );
  aspect = (GLfloat) width / height;
  gluPerspective( 45, aspect, 1.0, 10.0 );
  glMatrixMode( GL_MODELVIEW );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  ghDC = GetDC(Handle);
  dc=ghDC;
  if (!bSetupPixelFormat(ghDC))
    Close();
  ghRC = wglCreateContext(ghDC);
  wglMakeCurrent(ghDC, ghRC);
  initGL(ClientRect.Right, ClientRect.Bottom);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
  glViewport( 0, 0, ClientRect.Right, ClientRect.Bottom );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  scene.SceneInit();
  Timer1->Enabled = false;
  scene.DrawScene();
  Timer1->Enabled = true;
}
//---------------------------------------------------------------------------


