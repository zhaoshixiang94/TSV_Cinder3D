#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/Utilities.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"
#include "ParticleController.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "Add.h"

#define NUM_INITIAL_PARTICLES 500

using namespace ci;
using namespace ci::app;

class CinderProjectApp : public AppBasic {
public:
	void prepareSettings(Settings *settings);
	void setup();
	void update();
	void draw();

	string str;
	int count;
	//path filepath;

	// PARAMS
	params::InterfaceGlRef	mParams;

	// CAMERA
	CameraPersp			mCam;
	Quatf				mSceneRotation;
	float				mCameraDistance;
	Vec3f				mEye, mCenter, mUp;
	string				mSize;

	// CUBE
	Vec3f mTranslation;
	Vec3f mScale;
	Vec3f mRotation;

	ParticleController	mParticleController;

	bool				mCentralGravity;
	//path filepath;
};


void CinderProjectApp::prepareSettings(Settings *settings)
{
	settings->setWindowSize(1280, 720);
	settings->setFrameRate(60.0f);
}


void CinderProjectApp::setup()
{
	count = 2;
	//For File
	str = "C:\Tsv_MyProject.tsv";
		/*boost::lexical_cast<string>(getOpenFilePath());*/
	//getOpenFilePath();

	mCentralGravity = false;

	// SETUP CAMERA
	mCameraDistance = 500.0f;
	mEye = Vec3f(0.0f, 0.0f, mCameraDistance);
	mCenter = Vec3f::zero();
	mUp = Vec3f::yAxis();
	mCam.setPerspective(75.0f, getWindowAspectRatio(), 5.0f, 2000.0f);

	// SETUP PARAMS
	mParams = params::InterfaceGl::create("CinderProjectApp", Vec2i(200, 160));
	mParams->addParam("Scene Rotation", &mSceneRotation, "opened=1");
	mParams->addSeparator();
	mParams->addParam("Eye Distance", &mCameraDistance, "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w");
	mParams->addParam("Center Gravity", &mCentralGravity, "keyIncr=g");
	mParams->addSeparator();

	// CREATE PARTICLE CONTROLLER
	mParticleController.addParticles(NUM_INITIAL_PARTICLES);

	//CUBE
	mTranslation.x = (float)getWindowWidth() / 2;
	mTranslation.y = (float)getWindowHeight() / 2;
	mTranslation.z = 0.0f;

}

void CinderProjectApp::update()
{
	// UPDATE CAMERA
	mEye = Vec3f(0.0f, 0.0f, mCameraDistance);
	mCam.lookAt(mEye, mCenter, mUp);
	gl::setMatrices(mCam);
	gl::rotate(mSceneRotation);

	// UPDATE PARTICLE CONTROLLER
	if (mCentralGravity) mParticleController.pullToCenter(mCenter);
	mParticleController.update();

	//CUBE
	mScale.x = (500 / mCameraDistance) * 100;
	mScale.y = (500 / mCameraDistance) * 100;
	mScale.z = (500 / mCameraDistance) * 100;

	mRotation.x += 1.0f;
	mRotation.y += 1.0f;
}

void CinderProjectApp::draw()
{
	if (count == 2)
	{
		gl::clear(Color(0, 0, 0.01f), true);
		gl::enableDepthRead();
		gl::enableDepthWrite();

		// DRAW PARTICLES
		glColor4f(ColorA(1.0f, 1.0f, 1.0f, 1.0f));
		mParticleController.draw();

		// DRAW PARAMS WINDOW
		mParams->draw();

		//CUBE
		gl::setMatricesWindowPersp(getWindowWidth(), getWindowHeight());
		gl::enableDepthRead();
		gl::enableDepthWrite();

		gl::pushMatrices();
		gl::translate(mTranslation);
		gl::scale(mScale);
		//gl::rotate( mRotation );
		gl::rotate(mSceneRotation);

		vector<FileBox> v = V(str);
		vector<FileBox>::iterator pt;
		unsigned int size = v.size();

		if ((size % 2) == 0)
		{
			int i = 1;
			for (pt = v.begin(); pt != v.end(); pt++)
			{
				float y = (float)(0.125 + 0.25*(((int)size / 2) - i));
				float lx = (float)(1 + (6 / ((int)size - 1))*(i - 1));
				gl::color(0, 1, 1);
				gl::drawCube(Vec3f(0, -y, 0), Vec3f(lx, 0.25f, 1.0f));
				gl::color(1, 0, 0);
				gl::drawStrokedCube(Vec3f(0, -y, 0), Vec3f(lx, 0.25f, 1.0f));
				string Size = boost::lexical_cast<string>(ShowSize(*pt));
				mParams->addParam(ShowName(*pt)+"    "+ Size+"bt",&mSize);
				i++;
			}

		}
		else
		{
			int i = 1;
			for (pt = v.begin(); pt != v.end(); pt++)
			{
				float y = (float)(0.25*((((int)size + 1) / 2) - i));
				float lx = (float)(1 + (6 / ((int)size - 1))*(i - 1));
				gl::color(0, 1, 1);
				gl::drawCube(Vec3f(0, -y, 0), Vec3f(lx, 0.25f, 1.0f));
				gl::color(1, 0, 0);
				gl::drawStrokedCube(Vec3f(0, -y, 0), Vec3f(lx, 0.25f, 1.0f));
				string Size = boost::lexical_cast<string>(ShowSize(*pt));
				mParams->addParam(ShowName(*pt) + "    " + Size + "bt", &mSize);
				i++;
			}
		}
	}
}

CINDER_APP_BASIC(CinderProjectApp, RendererGl)