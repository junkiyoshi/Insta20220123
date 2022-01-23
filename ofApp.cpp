#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(0.5);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	float deg_span = 2;
	float len = 3;

	bool flag = true;
	int deg_len = 120;

	for (int radius = 20; radius < 720; radius += len) {

		int deg_start = ofMap(ofNoise(radius % 20, ofGetFrameNum() * 0.0035), 0, 1, -360, 360);
		if (flag) {

			deg_start += 180;
		}
		flag = !flag;

		for (float deg = deg_start; deg <= deg_start + deg_len; deg += 1) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3((radius + len * 0.5) * cos((deg + deg_span * 0.5) * DEG_TO_RAD), (radius + len * 0.5) * sin((deg + deg_span * 0.5) * DEG_TO_RAD), 0));
			vertices.push_back(glm::vec3((radius - len * 0.5) * cos((deg + deg_span * 0.5) * DEG_TO_RAD), (radius - len * 0.5) * sin((deg + deg_span * 0.5) * DEG_TO_RAD), 0));
			vertices.push_back(glm::vec3((radius - len * 0.5) * cos((deg - deg_span * 0.5) * DEG_TO_RAD), (radius - len * 0.5) * sin((deg - deg_span * 0.5) * DEG_TO_RAD), 0));
			vertices.push_back(glm::vec3((radius + len * 0.5) * cos((deg - deg_span * 0.5) * DEG_TO_RAD), (radius + len * 0.5) * sin((deg - deg_span * 0.5) * DEG_TO_RAD), 0));

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addTriangle(this->face.getNumVertices() - 1, this->face.getNumVertices() - 2, this->face.getNumVertices() - 3);
			this->face.addTriangle(this->face.getNumVertices() - 1, this->face.getNumVertices() - 3, this->face.getNumVertices() - 4);
			
			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 4);
			this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 3);

			if (deg == deg_start) {

				this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
			}
			else if(deg == deg_start + deg_len) {

				this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 4);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSetColor(255);
	this->face.draw();

	ofSetColor(0);
	this->frame.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}