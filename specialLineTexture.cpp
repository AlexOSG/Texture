/*测试自制纹理 2016.12.21*/
#include <osg/Image>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osg/BlendFunc>
#include <osg/TexGen>
#include <osg/ref_ptr>
#include <osg/TexEnv>
#include <osg/Material>

void main()
{
	osg::Group* root = new osg::Group;
	osg::Geode* gnode = new osg::Geode;
	root->addChild(gnode);
	osg::Geometry* geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
	osg::Vec3Array* normals = new osg::Vec3Array;

	vertex->push_back(osg::Vec3(-5, 0, 0));
	vertex->push_back(osg::Vec3(-5, 0, 5));
//	vertex->push_back(osg::Vec3(10, 0, 10));
	vertex->push_back(osg::Vec3(5, 0, 5));
	vertex->push_back(osg::Vec3(5, 0, 0));
	geom->setVertexArray(vertex);
	gnode->addDrawable(geom);
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	normals->push_back(osg::Vec3(0.0, -1.0, 0.0));
	normals->push_back(osg::Vec3(0.0, -1.0, 0.0));
//	normals->push_back(osg::Vec3(0.0, -1.0, 0.0));
	normals->push_back(osg::Vec3(0.0, -1.0, 0.0));
	normals->push_back(osg::Vec3(0.0, -1.0, 0.0));

	geom->setNormalArray(normals);
	geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

#if 1
	osg::ref_ptr<osg::Vec2Array> texCoord = new osg::Vec2Array;
	texCoord->push_back(osg::Vec2(0.0, 0.0));
	texCoord->push_back(osg::Vec2(1.0, 0.0));
	texCoord->push_back(osg::Vec2(1.0, 1.0));
	texCoord->push_back(osg::Vec2(0.0, 1.0));
	geom->setTexCoordArray(0, texCoord);
#endif

#if 1
	int _wavadensity = 4;
	float _waveWidthRadio = 0.7;
	int iwidth = _wavadensity* _waveWidthRadio;
	unsigned char * buff = new unsigned char[256 * 256 * 4];

	for (int i = 0; i < 256 * 256; i++)
	{
		buff[i * 4 + 0] = 255;
		buff[i * 4 + 1] = 0;
		buff[i * 4 + 2] = 0;
		float fTemp;
		if (i%_wavadensity > iwidth)
		{
			fTemp = (float)iwidth / (float)(i%_wavadensity);
		}
		else
			fTemp = 0;
		fTemp = fTemp * 255;
		buff[i * 4 + 3] = (int)fTemp;
		if (i % 256 == 255)
		{
			buff[i * 4 + 3] = (0) * 255;
		}
	}
	osg::ref_ptr<osg::Image> image1 = new osg::Image();
	image1->setImage(256, 256, 1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, buff, osg::Image::AllocationMode::USE_NEW_DELETE);
#endif
	osg::Texture2D* pTex = new osg::Texture2D;
	pTex->setImage(0,image1.get());
	pTex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	pTex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	pTex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	pTex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	gnode->getOrCreateStateSet()->setTextureAttributeAndModes(0, pTex, osg::StateAttribute::ON);

#if 1
	osg::Material* material = new osg::Material;
	material->setDiffuse(osg::Material::FRONT, osg::Vec4(1.0, 0.0, 0.0, 0.5));
	material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 0.0, 0.0, 0.5));
	material->setAlpha(osg::Material::FRONT_AND_BACK, 0.5);
	gnode->getOrCreateStateSet()->setAttribute(material, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	osg::BlendFunc* bf = new osg::BlendFunc;
	bf->setSource(GL_SRC_ALPHA);
	bf->setDestination(GL_ONE_MINUS_SRC_ALPHA);
	gnode->getOrCreateStateSet()->setAttributeAndModes(bf);

#endif

	//osg::ref_ptr<osg::TexGen> texGen = new osg::TexGen;
	//texGen->setMode(osg::TexGen::SPHERE_MAP);

	//osg::ref_ptr<osg::TexEnv> texEnv = new osg::TexEnv;
	//texEnv->setMode(osg::TexEnv::BLEND);
	//texEnv->setColor(osg::Vec4(0.6f, 0.6f, 0.6f, 0.0f));

	//osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
	//stateSet->setTextureAttributeAndModes(1, pTex, osg::StateAttribute::ON);
	//stateSet->setTextureAttributeAndModes(1, texGen.get(), osg::StateAttribute::ON);
	//stateSet->setTextureAttribute(1, texEnv.get());
	//gnode->setStateSet(stateSet.get());
	
	osgViewer::Viewer viewer;
	viewer.setSceneData(root);
	viewer.run();
}

//#include <osgDB/ReadFile>
//#include <osgViewer/Viewer> 
//#include <osg/Node>
//#include <osg/Geode>
//#include <osg/Geometry>
//#include <osg/Group>
//#include <osg/Texture2D>
//#include <osg/TexGen>
//#include <osg/TexEnv>
//
//void main()
//{
//	osgViewer::Viewer viewer;
//	osg::ref_ptr<osg::Group> root = new osg::Group();
//	osg::ref_ptr<osg::Node>  node = osgDB::readNodeFile("D:\\OpenSceneGraph-Data\\cow.osg");
//
//	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("D:\\OpenSceneGraph-Data\\Images\\Primitives.gif");
//
//	if (image.get())
//	{
//		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
//		texture->setImage(image.get());
//
//		//设置自动生成纹理坐标
//		osg::ref_ptr<osg::TexGen> texgen = new osg::TexGen();
//		texgen->setMode(osg::TexGen::SPHERE_MAP);
//
//		//设置纹理环境，模式为BLEND
//		osg::ref_ptr<osg::TexEnv> texenv = new osg::TexEnv;
//		texenv->setMode(osg::TexEnv::Mode::ADD);
//		texenv->setColor(osg::Vec4(0.6, 0.6, 0.6, 0.0));
//
//		//启动单元一自动生成纹理坐标，并使用纹理
//		osg::ref_ptr<osg::StateSet> state = new osg::StateSet;
//		state->setTextureAttributeAndModes(1, texture.get(), osg::StateAttribute::ON);
//		state->setTextureAttributeAndModes(1, texgen.get(), osg::StateAttribute::ON);
//		state->setTextureAttribute(1, texenv.get());
//
//		node->setStateSet(state.get());
//
//	}
//	root->addChild(node.get());
//	viewer.setSceneData(root.get());
//	viewer.realize();
//	viewer.run();
//}