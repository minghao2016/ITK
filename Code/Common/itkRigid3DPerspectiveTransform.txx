/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkRigid3DPerspectiveTransform.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#ifndef _itkRigid3DPerspectiveTransform_txx
#define _itkRigid3DPerspectiveTransform_txx

#include "itkRigid3DPerspectiveTransform.h"


namespace itk
{

// Constructor with default arguments
template<class ScalarType>
Rigid3DPerspectiveTransform<ScalarType>::
Rigid3DPerspectiveTransform()
{
  m_Offset.Fill( 0 );
  m_Rotation = VnlQuaternionType(0,0,0,1); // axis * sin(t/2), cos(t/2)
  m_DirectMatrix = m_Rotation.rotation_matrix();
  m_FocalDistance = 1.0;
  m_Height = 1.0;
  m_Width  = 1.0;
}
 

    
// Copy Constructor
template <class ScalarType>
Rigid3DPerspectiveTransform<ScalarType>
::Rigid3DPerspectiveTransform( const Rigid3DPerspectiveTransform<ScalarType> & other )
{
  m_Offset        = other.m_Offset;
  m_Rotation      = other.m_Rotation;
  m_FocalDistance = other.m_FocalDistance;
  m_Width         = other.m_Width;
  m_Height        = other.m_Height;
  m_DirectMatrix    = m_Rotation.rotation_matrix();
}

// Destructor
template<class ScalarType>
Rigid3DPerspectiveTransform<ScalarType>::
~Rigid3DPerspectiveTransform()
{
}


// Assignment Operator
template <class ScalarType>
const Rigid3DPerspectiveTransform<ScalarType> &
Rigid3DPerspectiveTransform<ScalarType>
::operator=( const Self & other )
{
  m_Offset        = other.m_Offset;
  m_Rotation      = other.m_Rotation;
  m_FocalDistance = other.m_FocalDistance;
  m_Width         = other.m_Width;
  m_Height        = other.m_Height;
  m_DirectMatrix    = m_Rotation.rotation_matrix();
  return *this;
}


// Print self
template<class ScalarType>
std::ostream &
Rigid3DPerspectiveTransform<ScalarType>::
PrintSelf(std::ostream &s) const
{
  s << m_Offset   << std::endl;
  s << m_Rotation << std::endl;
  s << m_Focal << std::endl;
  s << m_Height << std::endl;
  s << m_Width << std::endl;
  s << m_DirectMatrix   << std::endl;
  return s;
}


// Set rotation
template<class ScalarType>
void
Rigid3DPerspectiveTransform<ScalarType>::
SetRotation(const VnlQuaternionType &rotation )
{
  m_Rotation      = rotation;
  m_DirectMatrix  = m_Rotation.rotation_matrix();
  return;
}



// Transform a point
template<class ScalarType>
Rigid3DPerspectiveTransform<ScalarType>::OutputPointType
Rigid3DPerspectiveTransform<ScalarType>::
Transform(const InputPointType &point) const 
{
  InputPointType rigid =  m_DirectMatrix * point + m_Offset;
  OutputPointType result;
  TScalarType factor = m_Height / (rigid[0]-m_FocalDistance);
  result[0] = rigid[0] * factor + m_Width  / 2.0;
  result[1] = rigid[1] * factor + m_Height / 2.0;
  return result;
}

  
} // namespace

#endif
