//
//  ofxComposer.h
//  GPUBurner
//
//  Created by Patricio Gonzalez Vivo on 3/9/12.
//  Copyright (c) 2012 http://www.PatricioGonzalezVivo.com All rights reserved.
//

#ifndef OFXCOMPOSER
#define OFXCOMPOSER

#include "ofMain.h"
#include "ofxPatch.h"
#include "enumerations.h"

class ofxComposer : public ofNode {
    
public:
    
    ofxComposer();
    ~ofxComposer();
    
    //** LOOPS **//
    //
    void    update();
    void    customDraw();
    void    drawInspectorGUIs();
    
    //** SETTERS **//
    //
    void    setEdit(bool _state);
    void    setLinkType (nodeLinkType type);
    void    setNodesCount(int count);
    
    
    //** GETTERS **//
    //
    map<int,ofxPatch*> getPatches();
    map<int,ofxPatch*> getActivePatches();
    int     getPatchesLowestCoord(int encapsulatedId = MAIN_WINDOW);
    int     getPatchesHighestCoord(int encapsulatedId = MAIN_WINDOW);
    int     getPatchesLeftMostCoord(int encapsulatedId = MAIN_WINDOW);
    int     getPatchesRightMostCoord(int encapsulatedId = MAIN_WINDOW);
    int     getPatchesHighestYInspectorCoord(int encapsulatedId = MAIN_WINDOW);
    int     getPatchesHighestXInspectorCoord(int encapsulatedId = MAIN_WINDOW);
    bool    getEdit();
    nodeLinkType getLinkType();
    int     getNodesCount();
    
    
    //** OTHER FUNCTIONS **//
    //
    void    addPatch(ofxPatch* p, ofPoint _position);
    ofxPatch* operator[](int _nID){ if ( (_nID != -1) && (patches[_nID] != NULL) ) return patches[_nID]; };
    int     size(){return patches.size(); };
    void    movePatches(ofVec3f diff);
    void    scalePatches(float yDiff);
    void    updateConnectionsSize(ofxPatch* patch);
    void    deletePatchConection(ofxPatchDeleteEvent &patch_id);
    void    setDrawInspectors(bool drawInspectors_);
    
    // scroll
    //
    void    setDraggingGrip(bool dragging);
    void    setDraggingHGrip(bool dragging);
    bool    isDraggingGrip();
    bool    isDraggingHGrip();
    
    void    deactivateAllPatches();
    void    activateAllPatches();
    bool    arePatchesDeactivated();

    // encapsulate
    // returns id of encapsulated Patch
    // -1 if error
    int     encapsulate();
    void    uncapsulate(int encapsulatedId);
    int     getSelectedEncapsulated();
    int     getLastPatchEncapsulated(int encapsulatedId);
//    void    setWindowsIdForEncapsulated(int encapsulatedId, int winId);
//    void    restoreWindowsForEncapsulated(int previousWin);
    void    setOutputEncapsulated(int patchId, vector<int> encapsulatedPatches);
    void    restoreOutputEncapsulated(int lastPatchId);
//    void    setCameraForWindow(int winId, ofEasyCam cam);
    string  getLastEncapsulatedName(int encapsulatedId);
    bool    saveEncapsulatedSettings(ofxXmlSettings &XML, int encapsulatedId);
    bool    saveEncapsulatedSettingsToSnippet(ofxXmlSettings &XML, int encapsulatedId, map<int,int> newIdsMap);

protected:
    
    bool    connect( int _fromID, int _toID, int _nTexture, bool addInput );
    
    map<int,ofxPatch*>  patches;
    bool midiLearnActive;
    bool editAudioInActive;
    bool editOSCActive;
    
private:
    
    //** EVENTS **//
    //
    void    _mousePressed(ofMouseEventArgs &e);
    void    _mouseMoved(ofMouseEventArgs &e);
    void    _keyPressed(ofKeyEventArgs &e);
    void    _keyReleased(ofKeyEventArgs &e);
    void    _mouseReleased(ofMouseEventArgs &e);
    void    _windowResized(ofResizeEventArgs &e);
    void    _mouseDragged(ofMouseEventArgs &e);
    
    void    activePatch( int _nID);
    
    int     isAnyPatchHit(float x, float y, float z);
    bool    isAnyLinkHit();
    bool    isAnyPatchSelected;
    
    bool    disabledPatches;
    
    string  configFile;
    
    bool    bEditMode;
    
    // node select, and link vertex selected
    //
    int     selectedDot;
    int     selectedID;
    
    // nodes count
    //
    int     nodesCount;
    
    // node link type
    //
    nodeLinkType nodeLinkType;
    
    // align nodes
    //
    int     verticalAlign1, verticalAlign2, verticalAlign3, horizontalAlign1, horizontalAlign2, horizontalAlign3;
    
    // multiple select
    //
    ofRectangle multipleSelectRectangle;
    int     multipleSelectFromX;
    int     multipleSelectFromY;
    void    multipleSelectAndReset();
    bool    holdingCommand;
    
    // scroll
    //
    bool draggingGrip;
    bool draggingHGrip;
    
    // encapsulate
    int validateEncapsulation(vector<int> &patchesToEncapsulate);
    
    bool formsLoop(int _originId, int _toId);
    void resetAlreadyVisited();
};


#endif
