/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkNeighborhoodBinaryThresholdImageFunction.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkNeighborhoodBinaryThresholdImageFunction_txx
#define _itkNeighborhoodBinaryThresholdImageFunction_txx

#include "itkNumericTraits.h"
#include "itkConstSmartNeighborhoodIterator.h"

namespace itk
{

/**
 * Constructor
 */
template <class TInputImage>
NeighborhoodBinaryThresholdImageFunction<TInputImage>
::NeighborhoodBinaryThresholdImageFunction()
{
  m_Radius.Fill(1);
}


/**
 *
 */
template<class TInputImage>
void
NeighborhoodBinaryThresholdImageFunction<TInputImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  this->Superclass::PrintSelf(os,indent);
}


/**
 *
 */
template <class TInputImage>
bool
NeighborhoodBinaryThresholdImageFunction<TInputImage>
::EvaluateAtIndex(const IndexType& index) const
{
  int i;
  
  if( !m_Image )
    {
    return ( false );
    }
  
  if ( !this->IsInsideBuffer( index ) )
    {
    return ( false );
    }

  // Create an N-d neighborhood kernel, using a zeroflux boundary condition
  ConstSmartNeighborhoodIterator<InputImageType>
    it(m_Radius, m_Image, m_Image->GetBufferedRegion());

  // Set the iterator at the desired location
  it.SetLocation(index);

  // Walk the neighborhood
  bool allInside = true;
  PixelType lower = this->GetLower();
  PixelType upper = this->GetUpper();
  PixelType value;
  for (i = 0; i < it.Size(); ++i)
    {
    value = it.GetPixel(i);
    if (lower > value || value > upper)
      {
      allInside = false;
      break;
      }
    }

  return ( allInside );
}


} // namespace itk

#endif
