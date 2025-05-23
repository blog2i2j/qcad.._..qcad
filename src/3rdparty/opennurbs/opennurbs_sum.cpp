//
// Copyright (c) 1993-2022 Robert McNeel & Associates. All rights reserved.
// OpenNURBS, Rhinoceros, and Rhino3D are registered trademarks of Robert
// McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

ON_Sum::ON_Sum()
{
  Begin(0.0);
}

int ON_Sum::SummandCount() const
{
  return m_pos_count + m_neg_count + m_zero_count;
}

void ON_Sum::Begin( double starting_value )
{
  m_sum_err = 0.0;
  m_pos_sum = 0.0;
  m_neg_sum = 0.0;
  m_pos_sum1_count = 0;
  m_pos_sum2_count = 0;
  m_pos_sum3_count = 0;
  m_neg_sum1_count = 0;
  m_neg_sum2_count = 0;
  m_neg_sum3_count = 0;
  m_pos_count = 0;
  m_neg_count = 0;
  m_zero_count = 0;

  // initialize memory. Fixes https://mcneel.myjetbrains.com/youtrack/issue/RH-85423
  memset(m_pos_sum1, 0, sizeof(double) * sum1_max_count);
  memset(m_pos_sum2, 0, sizeof(double) * sum2_max_count);
  memset(m_pos_sum3, 0, sizeof(double) * sum3_max_count);

  memset(m_neg_sum1, 0, sizeof(double) * sum1_max_count);
  memset(m_neg_sum2, 0, sizeof(double) * sum2_max_count);
  memset(m_neg_sum3, 0, sizeof(double) * sum3_max_count);

  if ( starting_value > 0.0 )
  {
    m_pos_sum = starting_value;
  }
  else if ( starting_value < 0.0 )
  {
    m_neg_sum = starting_value;
  }
}

double ON_Sum::SortAndSum( int count, double* a )
{
  // note that the arrays passed to ON_Sum::SortAndSum() are all 
  // homogeneous in sign
  double s = 0.0;
  if ( count > 0 )
  {
    if ( count >= 2 )
    {
      ON_SortDoubleArray( ON::sort_algorithm::quick_sort, a, count );
      //double a0 = fabs(a[0]);
      //double a1 = fabs(a[count-1]);
      m_sum_err += ON_EPSILON*( fabs(a[count-1]) + count*fabs(a[0]) );
    }
    // test first item in the array for sign
    // fixes https://mcneel.myjetbrains.com/youtrack/issue/RH-85423
    if ( a[0] < 0.0 ) 
    {
      a += count-1;
      while (count--)
        s += *a--;
    }
    else
    {
      while (count--)
        s += *a++;
    }
  }
  return s;
}

void ON_Sum::Plus( double x, double dx )
{
  Plus(x);
  if ( ON_IsValid(dx) )
    m_sum_err += fabs(dx);
}

void ON_Sum::Plus( double x )
{
  if (x > 0.0)
  {
    m_pos_count++;
    m_pos_sum1[m_pos_sum1_count++] = x;
    if ( m_pos_sum1_count == sum1_max_count )
    {
      m_pos_sum2[m_pos_sum2_count++] = SortAndSum( m_pos_sum1_count, m_pos_sum1 );
      m_pos_sum1_count = 0;
      if ( m_pos_sum2_count == sum2_max_count )
      {
        m_pos_sum3[m_pos_sum3_count++] = SortAndSum( m_pos_sum2_count, m_pos_sum2 );
        m_pos_sum2_count = 0;
        if ( m_pos_sum3_count == sum3_max_count )
        {
          x = SortAndSum( m_pos_sum3_count, m_pos_sum3 );
          m_sum_err += ON_EPSILON*( fabs(x) + fabs(m_pos_sum) );
          m_pos_sum += x;
          m_pos_sum3_count = 0;
        }
      }
    }
  }
  else if ( x < 0.0 )
  {
    m_neg_count++;
    m_neg_sum1[m_neg_sum1_count++] = x;
    if ( m_neg_sum1_count == sum1_max_count )
    {
      m_neg_sum2[m_neg_sum2_count++] = SortAndSum( m_neg_sum1_count, m_neg_sum1 );
      m_neg_sum1_count = 0;
      if ( m_neg_sum2_count == sum2_max_count )
      {
        m_neg_sum3[m_neg_sum3_count++] = SortAndSum( m_neg_sum2_count, m_neg_sum2 );
        m_neg_sum2_count = 0;
        if ( m_neg_sum3_count == sum3_max_count )
        {
          x = SortAndSum( m_neg_sum3_count, m_neg_sum3 );
          m_sum_err += ON_EPSILON*( fabs(x) + fabs(m_neg_sum) );
          m_neg_sum += x;
          m_neg_sum3_count = 0;
        }
      }
    }
  }
  else
    m_zero_count++;
}



void ON_Sum::operator=(double x)
{
  Begin(x);
}

void ON_Sum::operator+=(double x)
{
  Plus(x);
}

void ON_Sum::operator-=(double x)
{
  Plus(-x);
}



double ON_Sum::Total( double* error_estimate )
{
  double x;
  if ( m_pos_sum1_count > 0 )
  {
    m_pos_sum2[m_pos_sum2_count++] = SortAndSum( m_pos_sum1_count, m_pos_sum1 );
    m_pos_sum1_count = 0;
  }
  if ( m_pos_sum2_count > 0 )
  {
    m_pos_sum3[m_pos_sum3_count++] = SortAndSum( m_pos_sum2_count, m_pos_sum2 );
    m_pos_sum2_count = 0;
  }
  if ( m_pos_sum3_count > 0 )
  {
    x = SortAndSum( m_pos_sum3_count, m_pos_sum3 );
    m_sum_err += ON_EPSILON*( fabs(x) + fabs(m_pos_sum) );
    m_pos_sum += x;
    m_pos_sum3_count = 0;
  }

  if ( m_neg_sum1_count > 0 )
  {
    m_neg_sum2[m_neg_sum2_count++] = SortAndSum( m_neg_sum1_count, m_neg_sum1 );
    m_neg_sum1_count = 0;
  }
  if ( m_neg_sum2_count > 0 )
  {
    m_neg_sum3[m_neg_sum3_count++] = SortAndSum( m_neg_sum2_count, m_neg_sum2 );
    m_neg_sum2_count = 0;
  }
  if ( m_neg_sum3_count > 0 )
  {
    x = SortAndSum( m_neg_sum3_count, m_neg_sum3 );
    m_sum_err += ON_EPSILON*( fabs(x) + fabs(m_neg_sum) );
    m_neg_sum += x;
    m_neg_sum3_count = 0;
  }

  if ( error_estimate )
  {
    *error_estimate = m_sum_err + ON_EPSILON*(fabs(m_pos_sum) + fabs(m_neg_sum));
  }

  return m_pos_sum + m_neg_sum;
}
