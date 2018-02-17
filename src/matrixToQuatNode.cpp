/**
    Copyright (c) 2018 Ryan Porter
    You may use, distribute, or modify this code under the terms of the MIT license.
*/

/**
extractMatrixPosition node
This node returns the orientation component of the input matrix as a quaternion.

    matrix (m) matrix
        
    output (o) quaternion
        outputX (ox) double
        outputY (oz) double
        outputZ (oy) double
        outputW (ow) double
*/

#include "matrixToQuatNode.h"

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnData.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>
#include <maya/MMatrix.h>
#include <maya/MPlug.h>
#include <maya/MPxNode.h>
#include <maya/MQuaternion.h>
#include <maya/MString.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MTypeId.h>


// Input Attributes
MObject MatrixToQuaternion::matrixAttr;


// Output Attributes
MObject MatrixToQuaternion::outputAttr;
    MObject MatrixToQuaternion::outputXAttr;
    MObject MatrixToQuaternion::outputYAttr;
    MObject MatrixToQuaternion::outputZAttr;
    MObject MatrixToQuaternion::outputWAttr;


void* MatrixToQuaternion::creator()
{
    return new MatrixToQuaternion();
}


MStatus MatrixToQuaternion::initialize()
{
    MStatus status;

    MFnCompoundAttribute c;
    MFnMatrixAttribute m;
    MFnNumericAttribute n;

    matrixAttr = m.create("matrix", "m", MFnMatrixAttribute::Type::kDouble, &status);

    outputXAttr = n.create("outputX", "ox", MFnNumericData::kDouble, 0.0, &status);
    outputYAttr = n.create("outputY", "oy", MFnNumericData::kDouble, 0.0, &status);
    outputZAttr = n.create("outputZ", "oz", MFnNumericData::kDouble, 0.0, &status);
    outputWAttr = n.create("outputW", "ow", MFnNumericData::kDouble, 0.0, &status);

    outputAttr = c.create("output", "o", &status);
    c.addChild(outputXAttr);
    c.addChild(outputYAttr);
    c.addChild(outputZAttr);
    c.addChild(outputWAttr);
    c.setWritable(false);
    c.setStorable(false);

    addAttribute(matrixAttr);
    addAttribute(outputAttr);

    attributeAffects(matrixAttr, outputAttr);

    return MStatus::kSuccess;
}


MStatus MatrixToQuaternion::compute(const MPlug& plug, MDataBlock& data)
{
    MStatus status;

    if (plug == this->outputAttr || plug.parent() == this->outputAttr)
    {
        MMatrix mat = data.inputValue(matrixAttr).asMatrix();
        MTransformationMatrix t(mat);

        MQuaternion q = t.rotation();

        MDataHandle outX = data.outputValue(outputXAttr);
        MDataHandle outY = data.outputValue(outputYAttr);
        MDataHandle outZ = data.outputValue(outputZAttr);
        MDataHandle outW = data.outputValue(outputWAttr);

        outX.setDouble(q.x);
        outY.setDouble(q.y);
        outZ.setDouble(q.z);
        outW.setDouble(q.w);

        outX.setClean();
        outY.setClean();
        outZ.setClean();
        outW.setClean();

        data.setClean(outputAttr);
    } else {
        return MStatus::kUnknownParameter;
    }

    return MStatus::kSuccess;   
}