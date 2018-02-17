/**
    Copyright (c) 2018 Ryan Porter
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

#pragma once

#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MString.h>
#include <maya/MTypeId.h>

class MatrixToRows : public MPxNode
{
public:
    virtual MStatus         compute(const MPlug& plug, MDataBlock& data);
    static  void*           creator();
    static  MStatus         initialize();

private:
    static inline MStatus   extractRow(MDataBlock& data, const MMatrix &mat, unsigned int row, unsigned int col, MObject &attr);

public:
    static MTypeId          NODE_ID;
    static MString          NODE_NAME;

    static MObject          matrixAttr;
    
    static MObject          outAttr;
    static MObject          out00Attr;
    static MObject          out01Attr;
    static MObject          out02Attr;
    static MObject          out03Attr;
    static MObject          out10Attr;
    static MObject          out11Attr;
    static MObject          out12Attr;
    static MObject          out13Attr;
    static MObject          out20Attr;
    static MObject          out21Attr;
    static MObject          out22Attr;
    static MObject          out23Attr;
    static MObject          out30Attr;
    static MObject          out31Attr;
    static MObject          out32Attr;
    static MObject          out33Attr;
};