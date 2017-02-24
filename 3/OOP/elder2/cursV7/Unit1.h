//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
	void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
    GLvoid initGL(GLsizei width, GLsizei height);
    HGLRC ghRC;
    HDC   ghDC;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};

class tScene
{
  protected:
     GLfloat longitude, latitude, longinc;
     GLdouble radius;
  public:
    GLvoid SceneInit();
    GLvoid DrawScene();
    GLvoid polarView(GLdouble radius, GLdouble twist, GLdouble latitude,
           		   GLdouble longitude);
};

class tSun : public tScene
{
  protected:
     GLfloat r,g,b;
     GLint slices,stacks;
     GLdouble rad;
     GLUquadricObj *obj;
  public:
     GLvoid sunInit(GLfloat r, GLfloat g, GLfloat b, GLdouble radius,
                         GLint slices, GLint stacks);
     GLvoid creatSun();
};

class tPlanet : public tSun
{
  protected:
     GLint number;
     GLfloat x,y,z;
  public:
     GLvoid planetInit(GLfloat r, GLfloat g, GLfloat b, GLdouble radius,
                        GLint slices, GLint stacks, GLfloat x,
                         GLfloat y, GLfloat z, GLint number, GLfloat latitude);
     GLvoid creatPlanet();
     GLvoid DrawPlanet();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
