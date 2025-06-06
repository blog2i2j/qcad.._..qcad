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

// obsolete V2 and V5 annotation objects
#include "opennurbs_internal_V2_annotation.h"
#include "opennurbs_internal_V5_annotation.h"

// This define is up here so anybody who want's to defeat the
// bozo vaccine has to be doing it on purpose.
#define BOZO_VACCINE_699FCC4262D4488c9109F1B7A37CE926

// Added for v5 - 12-10-2009 LW
ON_OBJECT_IMPLEMENT(ON_OBSOLETE_V5_TextExtra,ON_UserData,"D90490A5-DB86-49f8-BDA1-9080B1F4E976");

ON_OBSOLETE_V5_TextExtra::ON_OBSOLETE_V5_TextExtra()
{
  m_userdata_uuid = ON_CLASS_ID(ON_OBSOLETE_V5_TextExtra);
  m_application_uuid = ON_opennurbs5_id; // opennurbs.dll reads/writes this userdata
                                         // The id must be the version 5 id because
                                         // V6 SaveAs V5 needs to work, but SaveAs
                                         // V4 should not write this userdata.
  m_userdata_copycount = 1;
  SetDefaults();
}

ON_OBSOLETE_V5_TextExtra::~ON_OBSOLETE_V5_TextExtra()
{
}

ON_OBSOLETE_V5_TextExtra* ON_OBSOLETE_V5_TextExtra::TextExtension(ON_OBSOLETE_V5_TextObject* pText, bool bCreate)
{
  ON_OBSOLETE_V5_TextExtra* pExtra = 0;
  if(pText)
  {
    pExtra = ON_OBSOLETE_V5_TextExtra::Cast(pText->GetUserData(ON_CLASS_ID(ON_OBSOLETE_V5_TextExtra)));
    if(pExtra == 0 && bCreate)
    {
      pExtra = new ON_OBSOLETE_V5_TextExtra;
      if(pExtra)
      {
        if(!pText->AttachUserData(pExtra))
        {
          delete pExtra;
          pExtra = 0;
        }
      }
    }
  }
  return pExtra;
}

const
ON_OBSOLETE_V5_TextExtra* ON_OBSOLETE_V5_TextExtra::TextExtension(const ON_OBSOLETE_V5_TextObject* pText, bool bCreate)
{
  return TextExtension((ON_OBSOLETE_V5_TextObject*)pText, bCreate);
}

void ON_OBSOLETE_V5_TextExtra::SetDefaults()
{
  m_parent_uuid = ON_nil_uuid;
  
  m_color_source = 0;
  m_mask_color = 0;
  m_border_offset = 0.1;
}

void ON_OBSOLETE_V5_TextExtra::Dump( ON_TextLog& text_log ) const
{
  // do nothing
}

unsigned int ON_OBSOLETE_V5_TextExtra::SizeOf() const
{
  unsigned int sz = ON_UserData::SizeOf();
  sz += sizeof(*this) - sizeof(ON_UserData);
  return sz;
}

bool ON_OBSOLETE_V5_TextExtra::Write(ON_BinaryArchive& archive) const
{
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);

  if(rc) rc = archive.WriteUuid(m_parent_uuid);
  if(rc) rc = archive.WriteBool(m_bDrawMask);
  if(rc) rc = archive.WriteInt(m_color_source);
  if(rc) rc = archive.WriteColor(m_mask_color);
  if(rc) rc = archive.WriteDouble(m_border_offset);

  if(!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_OBSOLETE_V5_TextExtra::Read(ON_BinaryArchive& archive)
{
  int major_version = 1;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if(!rc)
    return false;
  if(major_version != 1)
    return false;

  if(rc) rc = archive.ReadUuid(m_parent_uuid);
  if(rc) rc = archive.ReadBool(&m_bDrawMask);
  if(rc) rc = archive.ReadInt(&m_color_source);
  if(rc) rc = archive.ReadColor(m_mask_color);
  if(rc) rc = archive.ReadDouble(&m_border_offset);

  if ( !archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool ON_OBSOLETE_V5_TextExtra::GetDescription( ON_wString& description)
{
  description = L"Userdata extension of ON_OBSOLETE_V2_TextObject";
  return true;
}

bool ON_OBSOLETE_V5_TextExtra::Archive() const
{
  // true to write to file
  return true;
}


ON_UUID ON_OBSOLETE_V5_TextExtra::ParentUUID() const
{
  return m_parent_uuid;
}

void ON_OBSOLETE_V5_TextExtra::SetParentUUID( ON_UUID parent_uuid)
{
  m_parent_uuid = parent_uuid;
}

bool ON_OBSOLETE_V5_TextExtra::DrawTextMask() const
{
  return m_bDrawMask;
}

void ON_OBSOLETE_V5_TextExtra::SetDrawTextMask(bool bDraw)
{
  m_bDrawMask = bDraw;
}

int ON_OBSOLETE_V5_TextExtra::MaskColorSource() const
{
  return m_color_source;
}

void ON_OBSOLETE_V5_TextExtra::SetMaskColorSource(int source)
{
  if(source == 1)
    m_color_source = 1;
  else
    m_color_source = 0;
}

ON_Color ON_OBSOLETE_V5_TextExtra::MaskColor() const
{
  return m_mask_color;
}

void ON_OBSOLETE_V5_TextExtra::SetMaskColor(ON_Color color)
{
  m_mask_color = color;
}

double ON_OBSOLETE_V5_TextExtra::MaskOffsetFactor() const
{
  return m_border_offset;
}

void ON_OBSOLETE_V5_TextExtra::SetMaskOffsetFactor(double offset)
{
  m_border_offset = offset;
}

//--------------------



// Added for v5 - 4-20-07 LW
ON_OBJECT_IMPLEMENT(ON_OBSOLETE_V5_DimExtra,ON_UserData,"8AD5B9FC-0D5C-47fb-ADFD-74C28B6F661E");

ON_OBSOLETE_V5_DimExtra::ON_OBSOLETE_V5_DimExtra()
{
  m_userdata_uuid = ON_CLASS_ID(ON_OBSOLETE_V5_DimExtra);
  m_application_uuid = ON_opennurbs5_id; // opennurbs.dll reads/writes this userdata
                                         // The id must be the version 5 id because
                                         // V6 SaveAs V5 needs to work, but SaveAs
                                         // V4 should not write this userdata.
  m_userdata_copycount = 1;
  SetDefaults();
}

ON_OBSOLETE_V5_DimExtra::~ON_OBSOLETE_V5_DimExtra()
{
}

static ON_OBSOLETE_V5_DimExtra* AnnotationExtension(ON_OBSOLETE_V5_Annotation* pDim, bool bCreate)
{
  ON_OBSOLETE_V5_DimExtra* pExtra = 0;
  if(pDim)
  {
    pExtra = ON_OBSOLETE_V5_DimExtra::Cast(pDim->GetUserData(ON_CLASS_ID(ON_OBSOLETE_V5_DimExtra)));
    if(pExtra == 0 && bCreate)
    {
      pExtra = new ON_OBSOLETE_V5_DimExtra;
      if( pExtra)
      {
        if(!pDim->AttachUserData(pExtra))
        {
          delete pExtra;
          pExtra = 0;
        }
      }
    }
  }
  return pExtra;
}

ON_OBSOLETE_V5_DimExtra* ON_OBSOLETE_V5_DimExtra::DimensionExtension(ON_OBSOLETE_V5_DimLinear* pDim, bool bCreate)
{
  return AnnotationExtension((ON_OBSOLETE_V5_Annotation*)pDim, bCreate);
}

const
ON_OBSOLETE_V5_DimExtra* ON_OBSOLETE_V5_DimExtra::DimensionExtension(const ON_OBSOLETE_V5_DimLinear* pDim, bool bCreate)
{
  return DimensionExtension((ON_OBSOLETE_V5_DimLinear*)pDim, bCreate);
}

ON_OBSOLETE_V5_DimExtra* ON_OBSOLETE_V5_DimExtra::DimensionExtension(ON_OBSOLETE_V5_DimRadial* pDim, bool bCreate)
{
  return AnnotationExtension((ON_OBSOLETE_V5_Annotation*)pDim, bCreate);
}

const
ON_OBSOLETE_V5_DimExtra* ON_OBSOLETE_V5_DimExtra::DimensionExtension(const ON_OBSOLETE_V5_DimRadial* pDim, bool bCreate)
{
  return DimensionExtension((ON_OBSOLETE_V5_DimRadial*)pDim, bCreate);
}

ON_OBSOLETE_V5_DimExtra* ON_OBSOLETE_V5_DimExtra::DimensionExtension(ON_OBSOLETE_V5_DimOrdinate* pDim, bool bCreate)
{
  return AnnotationExtension((ON_OBSOLETE_V5_Annotation*)pDim, bCreate);
}

const
ON_OBSOLETE_V5_DimExtra* ON_OBSOLETE_V5_DimExtra::DimensionExtension(const ON_OBSOLETE_V5_DimOrdinate* pDim, bool bCreate)
{
  return DimensionExtension((ON_OBSOLETE_V5_DimOrdinate*)pDim, bCreate);
}

void ON_OBSOLETE_V5_DimExtra::SetDefaults()
{
  m_partent_uuid = ON_nil_uuid;
  
  m_arrow_position = 0;
  m_text_rects = 0;
  m_distance_scale = 1.0;
  m_modelspace_basepoint = ON_3dPoint::Origin;
  m_detail_measured = ON_nil_uuid;
}

void ON_OBSOLETE_V5_DimExtra::Dump( ON_TextLog& text_log ) const
{
  // do nothing
}

unsigned int ON_OBSOLETE_V5_DimExtra::SizeOf() const
{
  unsigned int sz = ON_UserData::SizeOf();
  sz += sizeof(*this) - sizeof(ON_UserData);
  return sz;
}

bool ON_OBSOLETE_V5_DimExtra::Write(ON_BinaryArchive& archive) const
{
  int major_version = 1;
  int minor_version = 2;
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,major_version,minor_version);

  if(rc) rc = archive.WriteUuid( m_partent_uuid);
  if(rc) rc = archive.WriteInt( m_arrow_position);
  if(rc)
  {
    if( m_text_rects)
    {
      rc = archive.WriteInt( 7);
      rc = archive.WriteInt( 28, (const int*)m_text_rects);
    }
    else
      rc = archive.WriteInt( 0);

  }
  // 21 June 2010 Added distance scale, minor version 1
  if(rc) rc = archive.WriteDouble(m_distance_scale);

  // 27 Aug, 2014 Added detail measured, minor version 2
  if (rc) rc = archive.WriteUuid(m_detail_measured);

  if(!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_OBSOLETE_V5_DimExtra::Read(ON_BinaryArchive& archive)
{
  int major_version = 1;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if(!rc)
    return false;
  if(major_version < 1)
    return false;

  if(rc) rc = archive.ReadUuid(m_partent_uuid);
  if(rc) rc = archive.ReadInt(&m_arrow_position);

  int rect_count = 0;
  if(rc) rc = archive.ReadInt( &rect_count);
  if( rc && rect_count)
    rc = archive.ReadInt( rect_count, (int*)m_text_rects);

  // 21 June 2010 Added distance scale, minor version 1
  if (minor_version > 0)
  {
    if (rc) rc = archive.ReadDouble(&m_distance_scale);
  }

  // 27 Aug, 2014 Added detail measured, minor version 2
  if (minor_version > 1)
  {
    m_detail_measured = ON_nil_uuid;
    if (rc) rc = archive.ReadUuid(m_detail_measured);
  }

  if (!archive.EndRead3dmChunk())
    rc = false;

  return rc;
}

bool ON_OBSOLETE_V5_DimExtra::GetDescription( ON_wString& description)
{
  description = L"Userdata extension of ON_Dimensions";
  return true;
}

bool ON_OBSOLETE_V5_DimExtra::Archive() const
{
  // true to write to file
  return true;
}


ON_UUID ON_OBSOLETE_V5_DimExtra::ParentUUID() const
{
  return m_partent_uuid;
}

void ON_OBSOLETE_V5_DimExtra::SetParentUUID( ON_UUID partent_uuid)
{
  m_partent_uuid = partent_uuid;
}

int ON_OBSOLETE_V5_DimExtra::ArrowPosition() const
{
  return m_arrow_position;
}

void ON_OBSOLETE_V5_DimExtra::SetArrowPosition( int position)
{
  if( position > 0)
    m_arrow_position = 1;
  else if( position < 0)
    m_arrow_position = -1;
  else
    m_arrow_position = 0;
}

double ON_OBSOLETE_V5_DimExtra::DistanceScale() const
{
  return m_distance_scale;
}

void ON_OBSOLETE_V5_DimExtra::SetDistanceScale(double s)
{
  m_distance_scale = s;
}

void ON_OBSOLETE_V5_DimExtra::SetModelSpaceBasePoint(ON_3dPoint basepoint)
{
  m_modelspace_basepoint = basepoint;
}

ON_3dPoint ON_OBSOLETE_V5_DimExtra::ModelSpaceBasePoint() const
{
  return m_modelspace_basepoint;
}

ON_UUID ON_OBSOLETE_V5_DimExtra::DetailMeasured() const
{
  return m_detail_measured;
}

void ON_OBSOLETE_V5_DimExtra::SetDetailMeasured(ON_UUID detail_id)
{
  m_detail_measured = detail_id;
}


/*
const wchar_t* ON_OBSOLETE_V5_DimExtra::ToleranceUpperString() const
{
  return m_upper_string;
}

ON_wString& ON_OBSOLETE_V5_DimExtra::ToleranceUpperString()
{
  return m_upper_string;
}

void ON_OBSOLETE_V5_DimExtra::SetToleranceUpperString( const wchar_t* upper_string)
{
  m_upper_string = upper_string;
}

void ON_OBSOLETE_V5_DimExtra::SetToleranceUpperString( ON_wString& upper_string)
{
  m_upper_string = upper_string;
}

const wchar_t* ON_OBSOLETE_V5_DimExtra::ToleranceLowerString() const
{
  return m_lower_string;
}

ON_wString& ON_OBSOLETE_V5_DimExtra::ToleranceLowerString()
{
  return m_lower_string;
}

void ON_OBSOLETE_V5_DimExtra::SetToleranceLowerString( const wchar_t* lower_string)
{
  m_lower_string = lower_string;
}

void ON_OBSOLETE_V5_DimExtra::SetToleranceLowerString( ON_wString& lower_string)
{
  m_lower_string = lower_string;
}



const wchar_t* ON_OBSOLETE_V5_DimExtra::AlternateString() const
{
  return m_alt_string;
}

ON_wString& ON_OBSOLETE_V5_DimExtra::AlternateString()
{
  return m_alt_string;
}

void ON_OBSOLETE_V5_DimExtra::SetAlternateString( const wchar_t* alt_string)
{
  m_alt_string = alt_string;
}

void ON_OBSOLETE_V5_DimExtra::SetAlternateString( ON_wString& alt_string)
{
  m_alt_string = alt_string;
}

const wchar_t* ON_OBSOLETE_V5_DimExtra::AlternateToleranceUpperString() const
{
  return m_alt_upper_string;
}

ON_wString& ON_OBSOLETE_V5_DimExtra::AlternateToleranceUpperString()
{
  return m_alt_upper_string;
}

void ON_OBSOLETE_V5_DimExtra::SetAlternateToleranceUpperString( const wchar_t* upper_string)
{
  m_alt_upper_string = upper_string;
}

void ON_OBSOLETE_V5_DimExtra::SetAlternateToleranceUpperString( ON_wString& upper_string)
{
  m_alt_upper_string = upper_string;
}

const wchar_t* ON_OBSOLETE_V5_DimExtra::AlternateToleranceLowerString() const
{
  return m_alt_lower_string;
}

ON_wString& ON_OBSOLETE_V5_DimExtra::AlternateToleranceLowerString()
{
  return m_alt_lower_string;
}

void ON_OBSOLETE_V5_DimExtra::SetAlternateToleranceLowerString( const wchar_t* lower_string)
{
  m_alt_lower_string = lower_string;
}

void ON_OBSOLETE_V5_DimExtra::SetAlternateToleranceLowerString( ON_wString& lower_string)
{
  m_alt_lower_string = lower_string;
}
*/

//--------------------


ON_VIRTUAL_OBJECT_IMPLEMENT( ON_OBSOLETE_V5_Annotation,       ON_Geometry,    "8D820224-BC6C-46b4-9066-BF39CC13AEFB");
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V5_DimLinear,  ON_OBSOLETE_V5_Annotation, "BD57F33B-A1B2-46e9-9C6E-AF09D30FFDDE");
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V5_DimRadial,  ON_OBSOLETE_V5_Annotation, "B2B683FC-7964-4e96-B1F9-9B356A76B08B");
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V5_DimAngular, ON_OBSOLETE_V5_Annotation, "841BC40B-A971-4a8e-94E5-BBA26D67348E");
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V5_TextObject,       ON_OBSOLETE_V5_Annotation, "46F75541-F46B-48be-AA7E-B353BBE068A7");
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V5_Leader,           ON_OBSOLETE_V5_Annotation, "14922B7A-5B65-4f11-8345-D415A9637129");
ON_OBJECT_IMPLEMENT( ON_TextDot,           ON_Geometry,    "74198302-CDF4-4f95-9609-6D684F22AB37");
ON_OBJECT_IMPLEMENT( ON_OBSOLETE_V5_DimOrdinate,ON_OBSOLETE_V5_Annotation, "C8288D69-5BD8-4f50-9BAF-525A0086B0C3");

// class ON_OBSOLETE_V5_Annotation
//--------------------------------------------------------------------

int ON_OBSOLETE_V5_Annotation::V5_3dmArchiveDimStyleIndex() const
{
  return m_v5_3dm_archive_dimstyle_index;
}

void ON_OBSOLETE_V5_Annotation::SetV5_3dmArchiveDimStyleIndex(
  int V5_dim_style_index
)
{
  m_v5_3dm_archive_dimstyle_index = V5_dim_style_index;
}

void ON_OBSOLETE_V5_Annotation::Create()
{
  Destroy();

  m_textdisplaymode = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine;
  m_v5_3dm_archive_dimstyle_index = -1;
  m_textheight = 1.0;
}

void ON_OBSOLETE_V5_Annotation::Destroy()
{
  m_v5_3dm_archive_dimstyle_index = -1;

  // 10-27-03 LW memory leak prevention
  m_points.Empty();
  SetTextValue(0);
  SetTextFormula(0);
  m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing;
  m_plane = ON_xy_plane;
  m_userpositionedtext = false;
  m_justification = 0;
  m_annotative_scale = true;
}

void ON_OBSOLETE_V5_Annotation::EmergencyDestroy()
{
  m_points.EmergencyDestroy();
  m_usertext.EmergencyDestroy();
}

ON_OBSOLETE_V5_Annotation::ON_OBSOLETE_V5_Annotation()
{
  Create();
}

ON_OBSOLETE_V5_Annotation::~ON_OBSOLETE_V5_Annotation()
{
  Destroy();
}


ON_OBSOLETE_V5_Annotation* ON_OBSOLETE_V5_Annotation::CreateFromV2Annotation(
  const class ON_OBSOLETE_V2_Annotation& V2_annotation,
  const class ON_3dmAnnotationContext* annotation_context
)
{
  for (;;)
  {
    const ON_OBSOLETE_V2_Leader* V2_leader = ON_OBSOLETE_V2_Leader::Cast(&V2_annotation);
    if (nullptr == V2_leader && ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader == V2_annotation.m_type)
      V2_leader = static_cast<const ON_OBSOLETE_V2_Leader*>(&V2_annotation);
    if (nullptr == V2_leader)
      break;
    return ON_OBSOLETE_V5_Leader::CreateFromV2Leader(
      *V2_leader,
      annotation_context,
      nullptr
    );
  }

  for(;;)
  {
    const ON_OBSOLETE_V2_TextObject* V2_text_object = ON_OBSOLETE_V2_TextObject::Cast(&V2_annotation);
    if (nullptr == V2_text_object)
      break;
    return ON_OBSOLETE_V5_TextObject::CreateFromV2TextObject(
      *V2_text_object,
      annotation_context,
      nullptr
    );
  }

  for(;;)
  {
    const ON_OBSOLETE_V2_DimRadial* V2_radial_dimension = ON_OBSOLETE_V2_DimRadial::Cast(&V2_annotation);
    if (nullptr == V2_radial_dimension)
      break;
    return ON_OBSOLETE_V5_DimRadial::CreateFromV2RadialDimension(
      *V2_radial_dimension,
      annotation_context,
      nullptr
    );
  }

  for(;;)
  {
    const ON_OBSOLETE_V2_DimLinear* V2_linear_dimension = ON_OBSOLETE_V2_DimLinear::Cast(&V2_annotation);
    if (nullptr == V2_linear_dimension)
      break;
    return ON_OBSOLETE_V5_DimLinear::CreateFromV2LinearDimension(
      *V2_linear_dimension,
      annotation_context,
      nullptr
    );
  }
  
  for(;;)
  {
    const ON_OBSOLETE_V2_DimAngular* V2_angular_dimension = ON_OBSOLETE_V2_DimAngular::Cast(&V2_annotation);
    if (nullptr == V2_angular_dimension)
      break;
    return ON_OBSOLETE_V5_DimAngular::CreateFromV2AngularDimension(
      *V2_angular_dimension,
      annotation_context,
      nullptr
    );
  }

  return nullptr;
}

////void ON_OBSOLETE_V5_Annotation::Internal_SetDimStyleFromV6Annotation(
////  const class ON_Annotation& V6_annotation,
////  const class ON_3dmAnnotationContext* annotation_context
////)
////{
////  if (nullptr != annotation_context)
////    SetV6_DimStyleId(annotation_context->DimStyleId(), annotation_context->V5_ArchiveDimStyleIndex());
////  else
////    SetV6_DimStyleId(V6_annotation.DimensionStyleId(), ON_UNSET_INT_INDEX);
////}

ON_OBSOLETE_V5_Annotation* ON_OBSOLETE_V5_Annotation::CreateFromV6Annotation(
  const class ON_Annotation& V6_annotation,
  const class ON_3dmAnnotationContext* annotation_context
)
{
  const ON_Text* V6_text_object = ON_Text::Cast(&V6_annotation);
  if (nullptr != V6_text_object)
    return ON_OBSOLETE_V5_TextObject::CreateFromV6TextObject(*V6_text_object, annotation_context, nullptr);

  const ON_Leader* V6_leader = ON_Leader::Cast(&V6_annotation);
  if (nullptr != V6_leader)
    return ON_OBSOLETE_V5_Leader::CreateFromV6Leader(*V6_leader, annotation_context, nullptr);

  const ON_DimRadial* V6_dim_radial = ON_DimRadial::Cast(&V6_annotation);
  if (nullptr != V6_dim_radial)
    return ON_OBSOLETE_V5_DimRadial::CreateFromV6DimRadial(*V6_dim_radial, annotation_context, nullptr);

  const ON_DimLinear* V6_dim_linear = ON_DimLinear::Cast(&V6_annotation);
  if (nullptr != V6_dim_linear)
    return ON_OBSOLETE_V5_DimLinear::CreateFromV6DimLinear(*V6_dim_linear, annotation_context, nullptr);

  const ON_DimAngular* V6_dim_angle = ON_DimAngular::Cast(&V6_annotation);
  if (nullptr != V6_dim_angle)
    return ON_OBSOLETE_V5_DimAngular::CreateFromV6DimAngular(*V6_dim_angle, annotation_context, nullptr);

  const ON_DimOrdinate* V6_dim_ordinate = ON_DimOrdinate::Cast(&V6_annotation);
  if (nullptr != V6_dim_ordinate)
    return ON_OBSOLETE_V5_DimOrdinate::CreateFromV6DimOrdinate(*V6_dim_ordinate, annotation_context, nullptr);

  return nullptr;
}

bool ON_OBSOLETE_V5_Annotation::EvaluatePoint( const ON_ObjRef& objref, ON_3dPoint& P) const
{
  bool rc = false;
  switch( objref.m_component_index.m_type )
  {
  case ON_COMPONENT_INDEX::dim_linear_point:
  case ON_COMPONENT_INDEX::dim_radial_point:
  case ON_COMPONENT_INDEX::dim_angular_point:
  case ON_COMPONENT_INDEX::dim_ordinate_point:
  case ON_COMPONENT_INDEX::dim_text_point:
    {
      ON_2dPoint uv = Point(objref.m_component_index.m_index);
      if ( uv.IsValid() )
      {
        P = m_plane.PointAt(uv.x,uv.y);
        rc = true;
      }
    }
    break;
  default:
    // other enum values skipped on purpose
    break;
  }
  if (!rc)
  {
    P = ON_3dPoint::UnsetPoint;
  }
  return rc;
}

bool ON_OBSOLETE_V5_Annotation::IsValid( ON_TextLog* text_log ) const
{
  if ( !m_plane.IsValid() )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_Annotation - m_plane is not valid\n");
    }
    return false;
  }

  const int points_count = m_points.Count();

  int i;
  for ( i = 0; i < points_count; i++ )
  {
    if ( !m_points[i].IsValid() )
    {
      if ( text_log )
      {
        text_log->Print("ON_OBSOLETE_V5_Annotation - m_points[%d] is not valid.\n");
      }
      return false;
    }
  }

  switch ( m_type )
  {
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate:
    break;

  default:
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_Annotation - m_type = %d is not a valid enum value\n",m_type);
    }
    return false;
    break;
  }

  return true;
}

static bool WriteAnnotation2UserText_V4( ON_BinaryArchive& file, const ON_wString& s )
{
  bool rc;
  ON_wString s4;
  int len = s.Length();
  
  for(int i = 0; i < len; i++)
  {
    if(s[i] == '\r' || s[i] == '\n')
    {
      s4 += L'\r';
      s4 += L'\n';
      
      // May 24, 2012  Tim - Fix for RR 100260.  If we use a while here we
      // miss adding carriage returns where the user really meant to have a 
      // blank line.  If we only check the next character and then continue on
      // we preserve the blank lines.
      if(i < len-1 && (s[i+1] == L'\r' || s[i+1] == L'\n'))
        i++;
      continue;
    }
    s4 += s[i];
  }
  rc = file.WriteString(s4);
  return rc;
}

static bool WriteAnnotation2UserText_V5( ON_BinaryArchive& file, const ON_wString& s )
{
  bool rc;
  rc = file.WriteString( s);
  return rc;
}

bool ON_OBSOLETE_V5_Annotation::Write( ON_BinaryArchive& file ) const
{
  //int i;
  unsigned int ui;
  bool rc = false;
  bool bInChunk = (file.Archive3dmVersion() >= 5 );
  if ( bInChunk )
  {
    // 18 October 2007 Dale Lear
    //   I modified this code so that V5 files can add
    //   information in ON_OBSOLETE_V5_Annotation chunks without
    //   breaking past and future file IO.
    //   The opennurbs version number before this change was
    //   20071017*.  I changed the version to 20071018* when
    //   I checked in this IO change.  The reason I can get
    //   away with this is that nobody except developers has
    //   a copy of V5 Rhino.
    // 28 Aug, 2010 - Lowell - changed minor version 0->1 to write
    //   annotative scale flag
    // 24 September 2010 Dale Lear 
    //   I incremented chunk version to 1.2 and wrote the TextFormula() string.
    rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,3);
    if (!rc)
      return false;
  }
  else
  {
    // For archives with opennurbs version < 200710180
    // The code before version 200710180 does not properly
    // handle new additions to the ON_OBSOLETE_V5_Annotation chunk.  
    rc = file.Write3dmChunkVersion( 1, 0 );
  }

  while(rc)
  {
    ui = static_cast<unsigned char>(m_type);
    rc = file.WriteInt(ui);
    if ( !rc) break;

    ui = (unsigned int)m_textdisplaymode;    
    rc = file.WriteInt(ui);
    if ( !rc) break;

    // June 17, 2010 - Lowell - Added adjustment to position text
    // a little better in pre-v5 files.
    // There's no adjustment for right/left justify because we don't
    // know the width of the text here
    // This doesn't change the size or position of any fields being
    // written, but just adjusts the plane to tune up the alignment

    // 16 Nov, 2011 - Lowell - Change text to bottom left justified for pre-v5 files rr94270
    // This stuff is moved to CRhinoDoc::Write3DMHelper() so it will help with other file
    // formats too
    //ON_Plane plane = m_plane;
    //if(file.Archive3dmVersion() <= 4 && m_type == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock)
    //{
    //  double height = m_textheight;
    //  int lines = CountTextLines(m_usertext);
    //  double linefeed = ON_Font::m_default_linefeed_ratio;

    //  if(m_justification & tjBottom)
    //  {
    //    if(lines > 1)
    //    {
    //      ON_3dPoint p = plane.PointAt(0.0, -height * (lines-1) * linefeed);
    //      plane.SetOrigin(p);
    //    }
    //  }
    //  else if(m_justification & tjMiddle)
    //  {
    //    double h = height * (lines-1) * linefeed + height;
    //    ON_3dPoint p = plane.PointAt(0.0, h * 0.5);
    //    plane.SetOrigin(p);
    //  }
    //  else if(m_justification & tjTop)
    //  {
    //    ON_3dPoint p = plane.PointAt(0.0, -height);
    //    plane.SetOrigin(p);
    //  }
    //}
  
    rc = file.WritePlane(m_plane);
    if ( !rc) break;

    ON_2dPointArray points = m_points;
    int bUserPositionedText = m_userpositionedtext?1:0;
    switch( m_type )
    {
    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned:
    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear:
      if ( 4 == points.Count() )
      {
        // so old versions will read enough points.
        points.AppendNew();
        points[4].Set(0.5*(points[0].x + points[2].x),points[1].y);
        bUserPositionedText = false;
      }
      break;

    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular:
      //user positioned text is supported.
      break;

    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius:
    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter:
      // 9 August 2005 Dale Lear - radial dimensions do
      // not support user positioned text.  The never have
      // in Rhino, but the old files had 5 points in them.
      if ( 4 == points.Count() )
      {
        // so old versions will read enough points.
        points.AppendNew();
      }
      if ( points.Count() >= 5 )
      {
        points[4] = points[2];
      }
      bUserPositionedText = false;
      break;

    default:
      bUserPositionedText = false;
      break;
    }
    
    rc = file.WriteArray( points);
    if ( !rc) break;
    
    // June 17, 2010 - Lowell - Added support for writing word-wrapped text
    // to pre-v5 files with hard returns in place of wrapping markers
    rc = ( file.Archive3dmVersion() <= 4 )
       ? WriteAnnotation2UserText_V4(file,m_usertext)
       : WriteAnnotation2UserText_V5(file,m_usertext);
    if ( !rc) break;
    // 7-9-03 lw removed extra text string getting written
    
    rc = file.WriteInt( bUserPositionedText );
    if ( !rc) break;
    

    const bool bIsText = IsText();
    //rc = file.Write3dmReferencedComponentIndex(
    //  bIsText ? ON_ModelComponent::Type::TextStyle : ON_ModelComponent::Type::DimStyle, m_dimstyle_index );
    rc = file.WriteInt(m_v5_3dm_archive_dimstyle_index);
    if ( !rc) break;

    rc = file.WriteDouble( m_textheight);
    if ( !rc) break;

    if ( !bInChunk )
      break;

    // NOTE WELL - NEVER change the code in this function
    //             above this comment.  If you do, you will
    //             break reading and writing V4 files.
    //             Ask Dale Lear if you have any questions.

    // 18 October 2007 - Dale Lear added m_justification IO
    rc = file.WriteInt(m_justification);
    if ( !rc) 
      break;

    // 28 Aug 2010 - Lowell - Added flag for whether text gets scaled in modelspace
    rc = file.WriteBool(m_annotative_scale);
    if(!rc)
      break;

    // 24 September 2010 Dale Lear 
    //   I incremented chunk version to 1.2
    ON_wString text_formula = TextFormula();
    rc = file.WriteString(text_formula);
    if(!rc)
      break;

    // To write more ON_OBSOLETE_V5_Annotation fields, increment the minor version
    // number and write the new information here.

    // September 2015 Dale Lear
    //   I incremented chunk version to 1.3
    //   and separated text style and dim style
    //rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::TextStyle, bIsText ? m_dimstyle_index : -1 );
    //if ( !rc) break;
    //rc = file.Write3dmReferencedComponentIndex( ON_ModelComponent::Type::DimStyle, bIsText ? -1 : m_dimstyle_index );
    //if ( !rc) break;
    rc = file.WriteInt( bIsText ? m_v5_3dm_archive_dimstyle_index : -1 );
    if ( !rc) break;
    rc = file.WriteInt( bIsText ? -1 : m_v5_3dm_archive_dimstyle_index );
    if ( !rc) break;

    // Finished writing ON_OBSOLETE_V5_Annotation information
    break;
  }

  if ( bInChunk )
  {
    if ( !file.EndWrite3dmChunk() )
      rc = false;
  }

  return rc;
}

bool ON_OBSOLETE_V5_Annotation::Read( ON_BinaryArchive& file )
{
  // NOTE WELL - If you make any changes to this code,
  //             you break file IO for some annotation
  //             objects.  Please discuss all changes
  //             with Dale Lear BEFORE you check in any
  //             changes.

  Destroy();
  
  // If annotation is read from old files that do not contain
  // the m_annotative_scale setting, then m_annotative_scale 
  // must be false so the text behaves the way it did in old
  // files.  The "Destroy()" function above can set m_annotative_scale
  // any way that makes sense for new objects.
  m_annotative_scale = false;
  
  int major_version = 0;
  int minor_version = 0;
  bool rc = false;

  bool bInChunk = (file.Archive3dmVersion() >= 5 && file.ArchiveOpenNURBSVersion() >= 200710180);

  if ( bInChunk )
  {
    rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
    if ( !rc )
      return false;
  }
  else
  {
    rc = file.Read3dmChunkVersion(&major_version,&minor_version);
  }

  bool bIsText = false;
  int dim_style_index = ON_UNSET_INT_INDEX;
  int dim_style_index0 = ON_UNSET_INT_INDEX;
  int dim_style_index1 = ON_UNSET_INT_INDEX;
  int dim_style_index2 = ON_UNSET_INT_INDEX;
  while(rc)
  {
    if ( 1 != major_version )
    {
      rc = false;
      break;
    }

    unsigned int ui;
    rc = file.ReadInt(&ui);
    if (!rc) break;
    m_type = ON_INTERNAL_OBSOLETE::V5AnnotationTypeFromUnsigned(ui);

    rc = file.ReadInt(&ui);
    if (!rc) break;
    m_textdisplaymode = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode(ui);

    rc = file.ReadPlane( m_plane);
    if (!rc) break;

    rc = file.ReadArray( m_points);
    if (!rc) break;
    
    rc = file.ReadString( m_usertext);
    if (!rc) break;
    
    ui = 0;
    rc = file.ReadInt( &ui );
    if (!rc) break;
    m_userpositionedtext = ui ? true : false;

    // Initially, a single integer was used. It was either a text style index or a dim style index.
    // In August 2016, text styles were removed and font information is saved on ON_DimStyle.
    // When Read3dmReferencedComponentIndex() is called with the first parameter = ON_ModelComponent::Type::TextStyle,
    // it returns the value to use as a dimstyle index.
    bIsText = IsText();
    rc = file.Read3dmReferencedComponentIndex(
      bIsText ? ON_ModelComponent::Type::TextStyle : ON_ModelComponent::Type::DimStyle,
      &dim_style_index0
    );
    if (!rc) break;
    dim_style_index = dim_style_index0;
    
    rc = file.ReadDouble( &m_textheight);
    if (!rc) break;

    switch( m_type )
    {
    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned:
    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear:
      if ( m_points.Count() < 5 )
      {
        m_userpositionedtext = false;
      }
      break;

    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular:
      if ( m_points.Count() <= 0 )
      {
        m_userpositionedtext = false;
      }
      break;

    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius:
    case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter:
      // 9 August 2005 Dale Lear - radial dimensions do
      // not support user positioned text.  The never have
      // in Rhino, but the old files had 5 points in them.
      if ( 5 == m_points.Count() )
      {
        m_points.SetCount(4);
      }
      m_userpositionedtext = false;
      break;

    default:
      m_userpositionedtext = false;
      break;
    }

    if ( !bInChunk )
      break;

    // 18 October 2007 - Dale Lear added m_justification IO
    rc = file.ReadInt( &m_justification );
    if (!rc) break;

    if ( minor_version <= 0 )
      break;

    if(minor_version >= 1)
    {
      // 28 Aug, 2010 - Lowell - added reading annotative scale flag
      rc = file.ReadBool(&m_annotative_scale);
      if (!rc) break;

      if ( minor_version >= 2 )
      {
        // 24 September 2010 Dale Lear 
        //   I incremented chunk version to 1.2
        ON_wString text_formula;
        rc = file.ReadString(text_formula);
        if(!rc) break;
        SetTextFormula(static_cast< const wchar_t* >(text_formula));

        if (minor_version >= 3)
        {
          // September 2015 Dale Lear
          //   I incremented chunk version to 1.3
          //   and separated text style and dim style
          // In August 2016, text styles were removed and font information is saved on ON_DimStyle.
          // When Read3dmReferencedComponentIndex() is called with the first parameter = ON_ModelComponent::Type::TextStyle,
          // it returns the value to use as a dimstyle index.
          rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::TextStyle, &dim_style_index1);
          if (!rc) break;
          rc = file.Read3dmReferencedComponentIndex(ON_ModelComponent::Type::DimStyle, &dim_style_index2);
          if (!rc) break;
          dim_style_index = ON_UNSET_INT_INDEX;
        }
      }
    }

    // Read new additions to ON_OBSOLETE_V5_Annotation here

    break;
  }

  if ( bInChunk )
  {
    if (!file.EndRead3dmChunk() )
      rc = false;
  }

  //if (!bInChunk)
  {
    // If justification is 0, change it to top-left
    // and move the text point up by text height
    if (bIsText && 0 == m_justification)
    {
      m_justification = eTextJustification::tjTopLeft;
      m_plane.origin = m_plane.PointAt(0.0, m_textheight);
    }
  }

  if (ON_UNSET_INT_INDEX == dim_style_index)
  {
    if (bIsText)
    {
      if (dim_style_index0 > ON_UNSET_INT_INDEX && dim_style_index0 == dim_style_index1)
        dim_style_index = dim_style_index1;
      else
      {
        ON_ERROR("Unexpected text object dim style index.");
        if (dim_style_index1 >= 0)
          dim_style_index = dim_style_index1;
        else if (dim_style_index0 >= 0)
          dim_style_index = dim_style_index0;
        else if (dim_style_index2 >= 0)
          dim_style_index = dim_style_index2;
      }
    }
    else
    {
      // not text 
      if (dim_style_index0 > ON_UNSET_INT_INDEX && dim_style_index0 == dim_style_index2)
        dim_style_index = dim_style_index2;
      else
      {
        ON_ERROR("Unexpected dimension object dim style index.");
        if (dim_style_index2 >= 0)
          dim_style_index = dim_style_index2;
        else if (dim_style_index0 >= 0)
          dim_style_index = dim_style_index0;
        else if (dim_style_index1 >= 0)
          dim_style_index = dim_style_index1;
      }
    }
  }

  if (ON_UNSET_INT_INDEX != dim_style_index)
    this->SetV5_3dmArchiveDimStyleIndex( dim_style_index );

  // July 29, 2020 - Lowell
  // If somebody has managed to make a V5 file that has text with single "\n" chars to delineate lines,
  // and marks the text as "wrapped" it displays as text with various length lines.
  // V5 itself uses '\r\n' to mark hard returns and '\n' to mark lines made by paragraph wrapping
  // V6 and later ignore '\n' and convert '\r\n' to newlines and wraps the text to the specified 
  // wrapping width at runtime.
  // The only example of this kind of text formatting I've seen here is from a file referenced by
  // https://mcneel.myjetbrains.com/youtrack/issue/RH-59675
  // Uncommenting the following clause will convert all of the '\n' in V5 wrapped text to '\r\n'
  // causing V6 to make line breaks at those places.
  // The text will no longer be "wrapped", but will have hard returns at the end of each line
  // where it was wrapped in V5.
  ////////////////////////////////////
  //if (bInChunk && bIsText)
  //{
  //  const wchar_t* s0 = L"\n";
  //  const wchar_t* s1 = L"\r\n";
  //  const wchar_t* s2 = L"6C632E28-CF14-49D0-ADEE-DF6ACCAC74F1";
  //  if (m_usertext.Find(s0) > -1)
  //  {
  //    ON_wString usertext(m_usertext);
  //    usertext.Replace(s1, s2);
  //    usertext.Replace(s0, s1);
  //    usertext.Replace(s2, s1);
  //    m_usertext = usertext;
  //  }
  //}
  ////////////////////////////////////

  return rc;
}

ON::object_type ON_OBSOLETE_V5_Annotation::ObjectType() const
{
  return ON::annotation_object;
}

int ON_OBSOLETE_V5_Annotation::Dimension() const
{
  return 3;
}

bool ON_OBSOLETE_V5_Annotation::Transform( const ON_Xform& xform )
{
  ON_Geometry::Transform(xform);
  const double tol = 1.0e-4;
  ON_3dVector vx = Plane().xaxis;
  ON_3dVector vy = Plane().yaxis;
  vx.Transform(xform);
  vy.Transform(xform);
  double sx = vx.Length();
  double sy = vy.Length();
  if ((fabs(sx - 1.0) > tol && fabs(sx) > tol) ||
      (fabs(sy - 1.0) > tol && fabs(sy) > tol))
  {
    ON_Xform xfscale(ON_Xform::DiagonalTransformation(sx, sy, 1.0));

    ON_2dPoint p;
    for (int i = 0; i < m_points.Count(); i++)
    {
      p = Point(i);
      p.Transform(xfscale);
      SetPoint(i, p);
    }
  }
  // This scales the text height on text but not on dimensions
  if (ON_OBSOLETE_V5_Annotation::IsText())
  {
    SetHeight(sy * Height());
  }

  return m_plane.Transform(xform);
}

int ON_Plane_Repair(ON_Plane& plane)
{
  int rc;
  if ( plane.IsValid() )
  {
    rc = 1;
  }
  else
  {
    rc = 2;
    if (!plane.origin.IsValid())
    {
      plane.origin.Set(0.0,0.0,0.0);
    }

    bool bGoodX = (plane.xaxis.IsValid() && !plane.xaxis.IsZero() );
    bool bGoodY = (plane.yaxis.IsValid() && !plane.yaxis.IsZero() );
    bool bGoodZ = (plane.zaxis.IsValid() && !plane.zaxis.IsZero() );
    if ( bGoodX )
    {
      if ( fabs(plane.xaxis.Length()-1.0) > ON_SQRT_EPSILON )
        plane.xaxis.Unitize();
    }
    if ( bGoodY )
    {
      if ( fabs(plane.yaxis.Length()-1.0) > ON_SQRT_EPSILON )
        plane.yaxis.Unitize();
    }
    if ( bGoodZ )
    {
      if ( fabs(plane.zaxis.Length()-1.0) > ON_SQRT_EPSILON )
        plane.zaxis.Unitize();
    }

    if ( bGoodZ )
    {
      double x = bGoodX ? fabs(plane.zaxis*plane.xaxis) : 99.0;
      double y = bGoodX ? fabs(plane.zaxis*plane.yaxis) : 99.0;
      if ( x <= ON_SQRT_EPSILON )
      {
        if ( y > ON_SQRT_EPSILON )
        {
          plane.yaxis = ON_CrossProduct(plane.zaxis,plane.xaxis);
          plane.yaxis.Unitize();
        }
      }
      else if ( y <= ON_SQRT_EPSILON )
      {
        plane.xaxis = ON_CrossProduct(plane.yaxis,plane.zaxis);
        plane.xaxis.Unitize();
      }
      else if ( x <= y && x < 1.0 )
      {
        plane.yaxis = ON_CrossProduct(plane.zaxis,plane.xaxis);
        if( plane.yaxis.Unitize() )
        {
          plane.xaxis = ON_CrossProduct(plane.yaxis,plane.zaxis);
          plane.xaxis.Unitize();
        }
        else if ( y < 1.0 )
        {
          plane.CreateFromNormal( plane.origin, plane.zaxis );
        }
      }
      else if ( y < 1.0 )
      {
        plane.xaxis = ON_CrossProduct(plane.yaxis,plane.zaxis);
        if( plane.xaxis.Unitize() )
        {
          plane.yaxis = ON_CrossProduct(plane.zaxis,plane.xaxis);
          plane.yaxis.Unitize();
        }
        else
        {
          plane.CreateFromNormal( plane.origin, plane.zaxis );
        }
      }
    }
    else if ( bGoodX )
    {
      if ( bGoodY )
      {
        plane.zaxis = ON_CrossProduct(plane.xaxis,plane.yaxis);
        if ( plane.zaxis.Unitize() )
        {
          if ( fabs(plane.yaxis*plane.xaxis) > ON_SQRT_EPSILON )
          {
            plane.yaxis = ON_CrossProduct(plane.zaxis,plane.xaxis);
            plane.yaxis.Unitize();
          }
        }
        else
        {
          plane.yaxis.PerpendicularTo(plane.xaxis);
          plane.yaxis.Unitize();
          plane.zaxis = ON_CrossProduct(plane.xaxis,plane.yaxis);
          plane.zaxis.Unitize();
        }
      }
      else
      {
        plane.yaxis.PerpendicularTo(plane.xaxis);
        plane.yaxis.Unitize();
        plane.zaxis = ON_CrossProduct(plane.xaxis,plane.yaxis);
        plane.zaxis.Unitize();
      }
    }
    else if ( bGoodY )
    {
      plane.zaxis.PerpendicularTo(plane.yaxis);
      plane.zaxis.Unitize();
      plane.xaxis = ON_CrossProduct(plane.yaxis,plane.zaxis);
      plane.xaxis.Unitize();
    }
    else
    {
      plane.xaxis.Set(1.0,0.0,0.0);
      plane.yaxis.Set(0.0,1.0,0.0);
      plane.zaxis.Set(0.0,0.0,1.0);
    }
    plane.UpdateEquation();
  }
  return rc;
}

// overrides virtual ON_Geometry::Transform()
bool ON_OBSOLETE_V5_DimRadial::Transform( const ON_Xform& xform )
{
  // TODO fill in something that works for non-rigid transforms
  return ON_OBSOLETE_V5_Annotation::Transform(xform);
}

bool ON_OBSOLETE_V5_Leader::Transform( const ON_Xform& xform )
{
  bool rc = xform.IsIdentity();
  if ( !rc)
  {
    ON_Plane plane = m_plane;
    rc = plane.Transform(xform);
    if ( rc )
    {
      int i;
      const int point_count =  m_points.Count();
      ON_2dPointArray q(point_count);
      ON_2dPoint p2, q2;
      ON_3dPoint P, Q;
      bool bUpdatePoints = false;
      for ( i = 0; i < point_count && rc; i++ )
      {
        p2 = m_points[i];
        P = m_plane.PointAt( p2.x, p2.y );
        Q = xform*P;
        if( !plane.ClosestPointTo(Q,&q2.x,&q2.y) )
          rc = false;
        if ( fabs(p2.x - q2.x) <= ON_SQRT_EPSILON )
          q2.x = p2.x;
        else
          bUpdatePoints = true;
        if ( fabs(p2.y - q2.y) <= ON_SQRT_EPSILON )
          q2.y = p2.y;
        else
          bUpdatePoints = true;
        q.Append(q2);
      }

      if(rc)
      {
        ON_Geometry::Transform(xform);
        m_plane = plane;

        if ( bUpdatePoints )
          m_points = q;

        if ( m_points[0].x != 0.0 || m_points[0].y != 0.0 )
        {
          ON_2dVector v = m_points[0];
          if ( !v.IsZero() )
          {
            m_plane.origin = m_plane.PointAt(v.x,v.y);
            m_plane.UpdateEquation();
            v = -v;
            for ( i = 1; i < point_count; i++ )
            {
              m_points[i] += v;
            }
            m_points[0].Set(0.0,0.0);
          }
        }
      }
    }
  }
  return rc;
}

bool ON_OBSOLETE_V5_DimAngular::Transform( const ON_Xform& xform )
{
  // Dale Lear - this override fixes RR 11114 by correctly
  //             handling non uniform scaling.
  bool rc = xform.IsIdentity();
  if ( !rc)
  {
    ON_Plane plane = m_plane;
    if ( dim_pt_count == m_points.Count() && plane.Transform( xform ) )
    {
      rc = true;
      ON_3dPoint P[dim_pt_count], Q[dim_pt_count], A[3], B[3];
      ON_2dVector p2[dim_pt_count], q2[dim_pt_count], a[3], b[3];
      double r[3];
      int i;
      bool bUpdatePoints = false;
      double a0 = 0.0;
      double a1 = m_angle;
      a[0].Set( m_radius*cos(a0), m_radius*sin(a0) );
      a[1].Set( m_radius*cos(0.5*(a0+a1)), m_radius*sin(0.5*(a0+a1)) );
      a[2].Set( m_radius*cos(a1), m_radius*sin(a1) );
      for ( i = 0; i < dim_pt_count && rc; i++ )
      {
        p2[i] = m_points[i];
        P[i] = m_plane.PointAt( p2[i].x, p2[i].y );
        Q[i] = xform*P[i];
        if( !plane.ClosestPointTo(Q[i],&q2[i].x,&q2[i].y) )
          rc = false;
        if (   fabs(p2[i].x - q2[i].x) > ON_SQRT_EPSILON 
            || fabs(p2[i].y - q2[i].y) > ON_SQRT_EPSILON )
        {
          // transformation is not a rigid motion
          bUpdatePoints = true;
        }
      }

      for ( i = 0; i < 3 && rc; i++ )
      {
        A[i] = m_plane.PointAt( a[i].x, a[i].y );
        B[i] = xform*A[i];
        if( !plane.ClosestPointTo(B[i],&b[i].x,&b[i].y) )
          rc = false;
        r[i] = B[i].DistanceTo(plane.origin);
        if (   fabs(a[i].x - b[i].x) > ON_SQRT_EPSILON 
            || fabs(a[i].y - b[i].y) > ON_SQRT_EPSILON )
        {
          // transformation is not a rigid motion
          bUpdatePoints = true;
        }
        if ( r[i] < ON_SQRT_EPSILON )
          rc = false;
        else if ( r[i] > m_radius*(1.0+ON_SQRT_EPSILON) )
          bUpdatePoints = true;
        else if ( r[i] < m_radius*(1.0-ON_SQRT_EPSILON) )
          bUpdatePoints = true;
      }

      if (rc)
      {
        if ( bUpdatePoints )
        {
          ON_3dVector X = B[0] - plane.origin;
          X.Unitize();

          ON_3dVector Y1 = B[1] - plane.origin;
          Y1.Unitize();
          ON_3dVector Z1 = ON_CrossProduct(X,Y1);
          double z1 = Z1.Length();
          Z1.Unitize();

          ON_3dVector Y2 = B[2] - plane.origin;
          Y2.Unitize();
          ON_3dVector Z2 = ON_CrossProduct(X,Y2);
          double z2 = Z2.Length();
          Z2.Unitize();

          if ( z2 >= z1 && z2 >= 0.00001 ) // 4 April 2014 - Lowell - At 0.05, this was too big a tolerance
          {                               // when the dimension had previously been scaled by 0.001 etc.  Rh-25926
            plane.xaxis = X;
            plane.zaxis = Z2;
            if (Z1*Z2 < 0.0)
              plane.zaxis = -plane.zaxis;
            plane.yaxis = ON_CrossProduct(plane.zaxis,plane.xaxis);
            plane.yaxis.Unitize();
          }
          else if ( z1 >= 0.00001 )
          {
            plane.xaxis = X;
            plane.zaxis = Z1;
            plane.yaxis = ON_CrossProduct(plane.zaxis,plane.xaxis);
            plane.yaxis.Unitize();
          }
          else
          {
            rc = false;
          }

          if (rc)
          {
            plane.UpdateEquation();
            ON_3dVector V = B[2] - plane.origin;
            double x = V*plane.xaxis;
            double y = V*plane.yaxis;
            double angle = atan2(y,x);
            if ( angle < 0.0 )
              angle += 2.0*ON_PI;
            double radius = (r[0]+r[1]+r[2])/3.0;

            double arc_pt_angle = 1.0/3.0;
            if ( m_angle > 0.0 && m_points[arc_pt_index].IsValid() )
            {
              arc_pt_angle = atan2(m_points[arc_pt_index].y,m_points[arc_pt_index].x);
              if ( arc_pt_angle < 0.0 ) arc_pt_angle += 2.0*ON_PI;
              if ( arc_pt_angle > m_angle )
                arc_pt_angle = 1.0/3.0;
              else
                arc_pt_angle /= m_angle;

              if ( arc_pt_angle < 0.0 ) 
                arc_pt_angle = 0.0; 
              else if ( arc_pt_angle > 1.0 ) 
                arc_pt_angle = 1.0;
            }
            arc_pt_angle *= angle;


            ON_Geometry::Transform(xform);
            m_plane = plane;
            m_radius = radius;
            m_angle = angle;
            m_points[start_pt_index].Set(m_radius,0.0);
            m_points[end_pt_index].Set(m_radius*cos(m_angle),m_radius*sin(m_angle));
            m_points[arc_pt_index].Set(m_radius*cos(arc_pt_angle),m_radius*sin(arc_pt_angle));
            if ( m_userpositionedtext )
            {
              m_plane.ClosestPointTo(Q[userpositionedtext_pt_index],
                &m_points[userpositionedtext_pt_index].x,
                &m_points[userpositionedtext_pt_index].y
                );
            }
            else
            {
              m_points[userpositionedtext_pt_index].Set(m_radius*cos(0.5*m_angle),m_radius*sin(0.5*m_angle));
            }

          }
        }
        else
        {
          ON_Geometry::Transform(xform);
          m_plane = plane;
        }
      }
    }
  }

  return rc;
}

bool ON_OBSOLETE_V5_Annotation::IsText() const 
{ return (ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock == m_type); }

bool ON_OBSOLETE_V5_Annotation::IsLeader() const 
{ return (ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader == m_type); }

bool ON_OBSOLETE_V5_Annotation::IsDimension() const 
{ return (ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock != m_type && ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader != m_type); }

double ON_OBSOLETE_V5_Annotation::NumericValue() const
{ return ON_UNSET_VALUE; }

void ON_OBSOLETE_V5_Annotation::SetHeight( double ht) 
{ if( ht > ON_SQRT_EPSILON) m_textheight = ht; }

double ON_OBSOLETE_V5_Annotation::Height() const 
{ return m_textheight; }

void ON_OBSOLETE_V5_Annotation::SetType( ON_INTERNAL_OBSOLETE::V5_eAnnotationType type ) 
{ 
  m_type = type;
  if(type == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius)
    SetTextValue(ON_OBSOLETE_V5_DimRadial::DefaultRadiusText());
  else if(type == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter)
    SetTextValue(ON_OBSOLETE_V5_DimRadial::DefaultDiameterText());
  else
    SetTextValue(0);

  SetTextFormula(0);
}

ON_INTERNAL_OBSOLETE::V5_eAnnotationType ON_OBSOLETE_V5_Annotation::Type() const 
{ return m_type; }

void ON_OBSOLETE_V5_Annotation::SetPlane( const ON_Plane& plane ) 
{ m_plane = plane; }

const ON_Plane& ON_OBSOLETE_V5_Annotation::Plane() const 
{ return m_plane; }

void ON_OBSOLETE_V5_Annotation::SetPointCount( int count) 
{
  if( m_points.Count() < count)
  {
    m_points.Reserve( count);
    for( int i = m_points.Count(); i < count; i++)
      m_points.Append( ON_2dPoint());
  }
}

int ON_OBSOLETE_V5_Annotation::PointCount() const 
{ return m_points.Count(); }

void ON_OBSOLETE_V5_Annotation::SetPoints( const ON_2dPointArray& points ) 
{ m_points = points; }

const ON_2dPointArray& ON_OBSOLETE_V5_Annotation::Points() const 
{ return m_points; }

void ON_OBSOLETE_V5_Annotation::SetPoint( int idx, const ON_2dPoint& point )
{
  if ( idx >= 0 )
  {
    if ( idx < m_points.Count() )
      m_points[idx] = point;
    else if ( idx == m_points.Count() )
      m_points.Append(point);
  }
}

ON_2dPoint ON_OBSOLETE_V5_Annotation::Point( int idx ) const
{
  return ( idx >= 0 && idx < m_points.Count() ) 
         ? m_points[idx] 
         : ON_2dPoint( 0.0, 0.0 );
}

void ON_OBSOLETE_V5_Annotation::SetUserText( const wchar_t* text_value )
// ON_OBSOLETE_V5_Annotation::SetUserText is OBSOLETE - use ON_OBSOLETE_V5_Annotation::SetTextValue();
{
  SetTextValue( text_value );
}

const ON_wString& ON_OBSOLETE_V5_Annotation::UserText() const 
// ON_OBSOLETE_V5_Annotation::UserText() is OBSOLETE - use ON_OBSOLETE_V5_Annotation::TextValue();
{
  return m_usertext; 
}

void ON_OBSOLETE_V5_Annotation::SetUserPositionedText( int bMoved ) 
{ m_userpositionedtext = bMoved?true:false; }
bool ON_OBSOLETE_V5_Annotation::UserPositionedText() const 
{ return m_userpositionedtext; }


// Converts 2d points in annotation to 3d WCS points
bool ON_OBSOLETE_V5_Annotation::GetECStoWCSXform( ON_Xform& xform ) const
{
  ON_3dVector z = ON_CrossProduct( m_plane.xaxis, m_plane.yaxis );
  return xform.ChangeBasis( m_plane.origin, m_plane.xaxis, m_plane.yaxis, z,
                            ON_3dPoint::Origin, ON_3dVector::XAxis, ON_3dVector::YAxis, ON_3dVector::ZAxis );
}

// Converts from WCS 3d points to 2d points in annotation
bool ON_OBSOLETE_V5_Annotation::GetWCStoECSXform( ON_Xform& xform ) const
{
  ON_3dVector z = ON_CrossProduct( m_plane.xaxis, m_plane.yaxis );
  return xform.ChangeBasis( ON_3dPoint::Origin, ON_3dVector::XAxis, ON_3dVector::YAxis, ON_3dVector::ZAxis,
                            m_plane.origin, m_plane.xaxis, m_plane.yaxis, z );
}

void ON_OBSOLETE_V5_Annotation::ReservePoints( int count)
{
  m_points.SetCapacity( count);
  m_points.SetCount( count);
}

const wchar_t* ON_OBSOLETE_V5_Annotation::DefaultText() { return L""; }


void ON_OBSOLETE_V5_Annotation::SetTextDisplayMode( ON_INTERNAL_OBSOLETE::V5_TextDisplayMode mode)
{
  m_textdisplaymode = mode;
}

ON_INTERNAL_OBSOLETE::V5_TextDisplayMode ON_OBSOLETE_V5_Annotation::TextDisplayMode() const
{
  return m_textdisplaymode;
}

void ON_OBSOLETE_V2_Annotation::Internal_InitializeFromV5Annotation( 
  const ON_OBSOLETE_V5_Annotation& V5_annotation,
  const class ON_3dmAnnotationContext* annotation_context
) 
{
  SetType( V5_annotation.Type());
  SetTextDisplayMode( V5_annotation.TextDisplayMode());
  SetPlane( V5_annotation.Plane());
  SetPoints( V5_annotation.Points());
  SetUserText( V5_annotation.TextValue());
  SetDefaultText( V5_annotation.DefaultText());
  SetUserPositionedText( V5_annotation.UserPositionedText());
}

void ON_OBSOLETE_V5_Annotation::SetJustification( unsigned int justification)
{
  if(this->IsLeader())
    m_justification = justification;
}

unsigned int ON_OBSOLETE_V5_Annotation::Justification() const
{
  if(this->IsLeader())
    return   m_justification;
  else
    return 0;
}


//----- ON_OBSOLETE_V5_DimLinear ------------------------------------------
ON_OBSOLETE_V5_DimLinear::ON_OBSOLETE_V5_DimLinear()
{
  //ON_OBSOLETE_V5_DimExtra* pDE = new ON_OBSOLETE_V5_DimExtra;
  //if( pDE)
  //{
  //  if( !AttachUserData( pDE))
  //    delete pDE;
  //  else
  //    pDE->SetDefaults();
  //}

  m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear;
  m_textdisplaymode = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine;
  m_plane = ON_xy_plane;
  SetTextValue(DefaultText());
  SetTextFormula(0);
  m_points.Reserve(ON_OBSOLETE_V5_DimLinear::dim_pt_count);
  m_points.SetCount(ON_OBSOLETE_V5_DimLinear::dim_pt_count);
  m_points.Zero();
}

ON_OBSOLETE_V5_DimLinear::~ON_OBSOLETE_V5_DimLinear()
{
}

bool ON_OBSOLETE_V5_DimLinear::IsValid( ON_TextLog* text_log ) const
{
  if ( m_type != ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear && m_type != ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimLinear - m_type !=  ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear or ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned.\n");
    }
    return false;
  }

  if ( !ON_OBSOLETE_V5_Annotation::IsValid( text_log ))
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimLinear - invalid ON_OBSOLETE_V5_Annotation base class.\n");
    }
    return false;
  }

  if ( m_points.Count() != 5 )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimLinear - m_points.Count() = %d (should be 5).\n",m_points.Count());
    }
    return false;
  }

  if ( m_points[1].x != m_points[0].x )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimLinear - m_points[1].x = %g != %g = m_points[0].x (should be equal)\n",
                      m_points[1].x, m_points[0].x
                      );
    }
    return false;
  }

  if ( m_points[3].x != m_points[2].x )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimLinear - m_points[3].x = %g != %g = m_points[2].x\n",
                      m_points[3].x, m_points[2].x
                     );
    }
    return false;
  }

  if ( m_points[3].y != m_points[1].y )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimLinear - m_points[3].y = %g != %g = m_points[1].y\n",
                      m_points[3].y, m_points[1].y
                      );
    }
    return false;
  }

  return true;
}

bool ON_OBSOLETE_V5_DimLinear::Write(ON_BinaryArchive& archive) const
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_DimLinear
  //    V4 did not have a ON_OBSOLETE_V5_DimLinear::Write and simply called
  //    ON_OBSOLETE_V5_Annotation::Write.
  bool rc = false;
  bool bInChunk = (archive.Archive3dmVersion() >= 5);
  if ( bInChunk )
  {
    rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Write(archive)?true:false;
    if (!rc) break;
    if ( !bInChunk )
      break;

    // To write new fields, increment minor version number
    // and write values here.  Ask Dale Lear for help.

    break;
  }

  if ( bInChunk )
  {
    if (!archive.EndWrite3dmChunk())
      rc = false;
  }
  return rc;
}

bool ON_OBSOLETE_V5_DimLinear::Read(ON_BinaryArchive& archive)
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_DimLinear
  int major_version = 0;
  int minor_version = 0;
  bool rc = false;
  bool bInChunk = (archive.Archive3dmVersion() >= 5 && archive.ArchiveOpenNURBSVersion() >= 200710180);
  if ( bInChunk )
  {
    rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Read(archive)?true:false;
    if (!rc) break;
    if ( !bInChunk || minor_version <= 0 )
      break;

    // read future addition here

    break;
  }

  if ( bInChunk )
  {
    if ( !archive.EndRead3dmChunk() )
      rc = false;
  }
  return rc;
}

bool ON_OBSOLETE_V5_DimLinear::GetBBox(
        double* boxmin,
        double* boxmax,
        bool bGrowBox
        ) const
{
  ON_BoundingBox bbox;
  if ( bGrowBox )
  {
    bbox.m_min.x = boxmin[0]; 
    bbox.m_min.y = boxmin[1]; 
    bbox.m_min.z = boxmin[2];
    bbox.m_max.x = boxmax[0]; 
    bbox.m_max.y = boxmax[1]; 
    bbox.m_max.z = boxmax[2];
    if ( !bbox.IsValid() )
    {
      bbox.Destroy();
      bGrowBox = false;
    }
  }

  if ( 5 == m_points.Count() )
  {
    ON_3dPointArray P(5);
    ON_2dPoint uv;
    if ( m_userpositionedtext )
    {
      uv = m_points[0]; // point someplace in text
      P.Append( m_plane.PointAt(uv.x,uv.y) );
    }

    P.Append( m_plane.origin );

    uv.x = 0.0;
    uv.y = m_points[1].y;
    P.Append( m_plane.PointAt(uv.x,uv.y) );

    uv = m_points[2];
    P.Append( m_plane.PointAt(uv.x,uv.y) );

    uv.y = m_points[1].y;
    P.Append( m_plane.PointAt(uv.x,uv.y) );
    bGrowBox = P.GetBBox(&bbox.m_min.x, &bbox.m_max.x, bGrowBox);
  }

  if ( bGrowBox )
  {
    boxmin[0] = bbox.m_min.x; 
    boxmin[1] = bbox.m_min.y; 
    boxmin[2] = bbox.m_min.z; 
    boxmax[0] = bbox.m_max.x; 
    boxmax[1] = bbox.m_max.y; 
    boxmax[2] = bbox.m_max.z; 
  }

  return bGrowBox;
}




bool ON_OBSOLETE_V5_DimLinear::GetTightBoundingBox( 
		ON_BoundingBox& tight_bbox, 
    bool bGrowBox,
		const ON_Xform* xform
    ) const
{
  if ( 5 == m_points.Count() )
  {
    ON_3dPointArray P(5);
    // 18 Oct 2012 - Lowell - Fixed this to add all of the points to the bbox rr116270
    for(int i = 0; i < 5; i++)
      P.Append( m_plane.PointAt(m_points[i].x,m_points[i].y) );

    if ( P.GetTightBoundingBox( tight_bbox, bGrowBox, xform ) )
      bGrowBox = true;
  }
  else if ( bGrowBox && !tight_bbox.IsValid() )
  {
    tight_bbox.Destroy();
    bGrowBox = false;
  }

  return (0!=bGrowBox);
}

int ON_OBSOLETE_V5_DimLinear::Repair()
{
  // returns 0 = unable to repair
  //         1 = in perfect condition
  //         2 == repaired.

  const int ext0_pt_index   = ON_OBSOLETE_V5_DimLinear::ext0_pt_index;
  const int arrow0_pt_index = ON_OBSOLETE_V5_DimLinear::arrow0_pt_index;
  const int ext1_pt_index   = ON_OBSOLETE_V5_DimLinear::ext1_pt_index;
  const int arrow1_pt_index = ON_OBSOLETE_V5_DimLinear::arrow1_pt_index;
  const int userpositionedtext_pt_index = ON_OBSOLETE_V5_DimLinear::userpositionedtext_pt_index;
  const int dim_pt_count    = ON_OBSOLETE_V5_DimLinear::dim_pt_count;

  int rc = 0;
  if (    m_points.Count() >= dim_pt_count 
       && m_points[ext0_pt_index].IsValid() 
       && m_points[ext1_pt_index].IsValid() )
  {
    rc = 1;
    if ( !m_plane.IsValid() )
    {
      rc = ON_Plane_Repair(m_plane);
    }

    if ( m_points.Count() > dim_pt_count )
    {
      rc = 2;
      m_points.SetCount(dim_pt_count);
    }

    // m_points[ext0_pt_index] must be at (0,0)
    ON_2dVector v = m_points[ext0_pt_index];
    double d;
    int i;
    if ( !v.IsZero() )
    {
      rc = 2;
      m_plane.origin = m_plane.PointAt(v.x,v.y);
      m_plane.UpdateEquation();
      v = -v;
      for ( i = 0; i < dim_pt_count; i++ )
      {
        m_points[i] += v;
      }
      m_points[ext0_pt_index].Set(0.0,0.0);
    }

    if ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned == m_type && (m_points[ext1_pt_index].x < 0.0 || m_points[ext1_pt_index].y != 0.0) )
    {
      rc = 2;
      // Aligned dims must have m_points[ext1_pt_index].x = m_points[ext0_pt_index].x
      if (   m_points[ext1_pt_index].x > 100.0*ON_SQRT_EPSILON
          && fabs(m_points[ext1_pt_index].y) <= ON_SQRT_EPSILON )
      {
        m_points[ext1_pt_index].y = 0.0;
      }
      else
      {
        // Dimension line parallel to point0 -> point2
        // rotate the plane so p2 is on the x axis
        v = m_points[ext1_pt_index];
        d = v.Length();
        v.Unitize();
        m_plane.Rotate(v.y,v.x,m_plane.zaxis,m_plane.origin);

        // rotate points in opposite direction
        v.y = -v.y; 
        for ( i = 0; i < dim_pt_count; i++ )
        {
          ON_2dPoint p = m_points[i];
          m_points[i].Set( v.x*p.x - v.y*p.y, v.y*p.x + v.x*p.y );
        }
        m_points[ext0_pt_index].Set(0.0,0.0);
        m_points[ext1_pt_index].Set(d,0.0);
      }
    }
    else if ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear != m_type )
    {
      rc = 2;
      m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear;
    }

    if ( m_points[arrow0_pt_index].x != m_points[ext0_pt_index].x )
    {
      rc = 2;
      m_points[arrow0_pt_index].x = m_points[ext0_pt_index].x;
    }

    if ( m_points[arrow1_pt_index].x != m_points[ext1_pt_index].x )
    {
      rc = 2;
      m_points[arrow1_pt_index].x = m_points[ext1_pt_index].x;
    }

    if ( !ON_IsValid(m_points[arrow0_pt_index].y) )
    {
      rc = 2;
      if ( !ON_IsValid(m_points[arrow1_pt_index].y) )
        m_points[arrow1_pt_index].y = 0.5*(m_points[ext0_pt_index].y + m_points[ext1_pt_index].y);
      m_points[arrow0_pt_index].y = m_points[arrow1_pt_index].y;
    }
    else if ( !ON_IsValid(m_points[arrow1_pt_index].y) )
    {
      rc = 2;
      m_points[arrow1_pt_index].y = m_points[arrow0_pt_index].y;
    }
    else if ( m_points[arrow0_pt_index].y != m_points[arrow1_pt_index].y )
    {
      rc = 2;
      d = 0.5*(m_points[arrow0_pt_index].y + m_points[arrow1_pt_index].y);
      m_points[arrow0_pt_index].y = d;
      m_points[arrow1_pt_index].y = d;
    }

    if ( m_userpositionedtext )
    {
      if ( !m_points[userpositionedtext_pt_index].IsValid() )
      {
        rc = 2;
        m_userpositionedtext = false;
      }
    }
    
    if ( !m_userpositionedtext )
    {
      if (    m_points[userpositionedtext_pt_index].y != m_points[arrow0_pt_index].y
           || m_points[userpositionedtext_pt_index].x != 0.5*(m_points[arrow0_pt_index].x + m_points[arrow1_pt_index].x) )
      {
        rc = 2;
        m_points[userpositionedtext_pt_index].y = m_points[arrow0_pt_index].y;
        m_points[userpositionedtext_pt_index].x = 0.5*(m_points[arrow0_pt_index].x + m_points[arrow1_pt_index].x);
      }
    }

    if ( !m_plane.IsValid() )
    {
      rc = 2;
      ON_Plane_Repair(m_plane);
    }
  }
  return rc;
}

bool ON_OBSOLETE_V5_DimLinear::Transform( const ON_Xform& xform )
{
  // Dale Lear - this override fixes RR 11114 by correctly
  //             handling non uniform scaling.
  bool rc = xform.IsIdentity();
  if ( !rc)
  {
    ON_Plane plane = m_plane;
    if ( dim_pt_count == m_points.Count() && plane.Transform( xform ) )
    {
      rc = true;
      ON_3dPoint P[dim_pt_count], Q[dim_pt_count];
      ON_2dVector p2[dim_pt_count], q2[dim_pt_count];
      int i;
      bool bUpdatePoints = false;
      for ( i = 0; i < dim_pt_count && rc; i++ )
      {
        p2[i] = m_points[i];
        P[i] = m_plane.PointAt( p2[i].x, p2[i].y );
        Q[i] = xform*P[i];
        if( !plane.ClosestPointTo(Q[i],&q2[i].x,&q2[i].y) )
          rc = false;
        if (   fabs(p2[i].x - q2[i].x) > ON_SQRT_EPSILON 
            || fabs(p2[i].y - q2[i].y) > ON_SQRT_EPSILON )
        {
          // transformation is not in SL3
          bUpdatePoints = true;
        }
      }

      if (rc)
      {
        ON_Geometry::Transform(xform);
        m_plane = plane;
        if ( bUpdatePoints )
        {
          for ( i = 0; i < dim_pt_count && rc; i++ )
          {
            m_points[i] = q2[i];
          }
          // Repair() will properly align the arrow points, etc.
          Repair();
        }
      }
    }
  }

  return rc;
}

double ON_OBSOLETE_V5_DimLinear::NumericValue() const
{
  // Use y coords of ext points instead of 3d distance
  // to reduce noise in the answer.
  return (m_points.Count() >= dim_pt_count) 
         ? fabs(m_points[ext0_pt_index].x - m_points[ext1_pt_index].x) 
         : 0.0;
}

int ON_OBSOLETE_V5_DimLinear::StyleIndex() const
{
  return ON_OBSOLETE_V5_Annotation::V5_3dmArchiveDimStyleIndex();
}

void ON_OBSOLETE_V5_DimLinear::SetStyleIndex( int i)
{
  ON_OBSOLETE_V5_Annotation::SetV5_3dmArchiveDimStyleIndex( i);
}

/*

    ext0_pt_index    = 0, // end of first extension line
    arrow0_pt_index  = 1, // arrowhead tip on first extension line
    ext1_pt_index    = 2, // end of second extension line
    arrow1_pt_index  = 3, // arrowhead tip on second extension line
    dim_pt_count     = 5, // number of m_points[] in an angular dim

    // Points calculated from values in m_points[]
    text_pivot_pt = 10000 // center of dimension text
    dim_mid_pt    = 10001 // midpoint of dimension line

*/

ON_2dPoint ON_OBSOLETE_V5_DimLinear::Dim2dPoint( int point_index ) const
{
  ON_2dPoint p2;
  if ( m_points.Count() < dim_pt_count )
  {
    p2.x = p2.y = ON_UNSET_VALUE;
  }
  else
  {
    if ( text_pivot_pt == point_index )
    {
      point_index = m_userpositionedtext ? userpositionedtext_pt_index : dim_mid_pt;
    }

    const ON_2dPoint* points = m_points.Array();
    switch(point_index)
    {
    case ext0_pt_index:
      p2 = points[0];
      break;

    case arrow0_pt_index:
      p2.x = points[0].x;
      p2.y = points[1].y;
      break;

    case ext1_pt_index:
      p2 = points[2];
      break;

    case arrow1_pt_index:
      p2.x = points[2].x;
      p2.y = points[1].y;
      break;

    case userpositionedtext_pt_index:
      p2.x = points[4].x;
      p2.y = points[4].y;
      break;

    case dim_mid_pt:
      p2.x = 0.5*(points[0].x + points[2].x);
      p2.y = points[1].y;
      break;

    default:
      p2.x = p2.y = ON_UNSET_VALUE;
      break;
    }
  }
  return p2;
}

ON_3dPoint ON_OBSOLETE_V5_DimLinear::Dim3dPoint( int point_index ) const
{
  ON_2dPoint p2 = Dim2dPoint(point_index);
  return (ON_UNSET_VALUE == p2.x) ? ON_3dPoint::UnsetPoint : m_plane.PointAt(p2.x,p2.y);
}

ON_OBSOLETE_V2_TextObject* ON_OBSOLETE_V2_TextObject::CreateFromV5TextObject(
  const class ON_OBSOLETE_V5_TextObject& V5_text_object,
  const ON_3dmAnnotationContext* annotation_context,
  ON_OBSOLETE_V2_TextObject* destination
)
{
  if (nullptr == annotation_context)
    annotation_context = &ON_3dmAnnotationContext::Default;
  const ON_DimStyle& dim_style = annotation_context->DimStyle();

  ON_OBSOLETE_V2_TextObject* V2_text_object
    = (nullptr != destination)
    ? destination
    : new ON_OBSOLETE_V2_TextObject();
  V2_text_object->Internal_InitializeFromV5Annotation(V5_text_object,annotation_context);

  V2_text_object->m_facename = dim_style.Font().WindowsLogfontName();

  const double V5_text_height = V5_text_object.Height();
  V2_text_object->m_fontweight = 400;
  V2_text_object->m_height = V5_text_height;

  if (V2_text_object->m_plane.IsValid())
  {
    // 8-20-03 lw convert from lower-left to upper-left reference point
    V2_text_object->m_plane.origin += V2_text_object->m_plane.yaxis * 1.1 * V5_text_height;
    V2_text_object->m_plane.UpdateEquation();
  }
  
  return V2_text_object;
}

ON_OBSOLETE_V2_DimAngular* ON_OBSOLETE_V2_DimAngular::CreateFromV5AngularDimension(
  const class ON_OBSOLETE_V5_DimAngular& V5_angular_dimension,
  const ON_3dmAnnotationContext* annotation_context,
  ON_OBSOLETE_V2_DimAngular* destination
)
{
  ON_OBSOLETE_V2_DimAngular* V2_angular_dimension
    = (nullptr != destination)
    ? destination
    : new ON_OBSOLETE_V2_DimAngular();
  V2_angular_dimension->Internal_InitializeFromV5Annotation(V5_angular_dimension,annotation_context);
  ON_SimpleArray<ON_2dPoint> V5_points(V5_angular_dimension.m_points);
  V2_angular_dimension->m_points.SetCount(0);
  V2_angular_dimension->SetPoint(0, ON_3dPoint(V5_angular_dimension.Point(1)));
  V2_angular_dimension->SetPoint(1, ON_3dPoint(V5_angular_dimension.Point(2)));
  V2_angular_dimension->SetPoint(2, ON_3dPoint(V5_angular_dimension.Point(3)));
  V2_angular_dimension->SetPoint(3, ON_3dPoint(V5_angular_dimension.Point(0))); // text point or apex
  V2_angular_dimension->SetAngle( V5_angular_dimension.Angle());
  V2_angular_dimension->SetRadius( V5_angular_dimension.Radius());

  return V2_angular_dimension;
}

ON_OBSOLETE_V2_DimRadial* ON_OBSOLETE_V2_DimRadial::CreateFromV5RadialDimension(
  const class ON_OBSOLETE_V5_DimRadial& V5_linear_dimension,
  const ON_3dmAnnotationContext* annotation_context,
  ON_OBSOLETE_V2_DimRadial* destination
)
{
  ON_OBSOLETE_V2_DimRadial* V2_radial_dimension
    = (nullptr != destination)
    ? destination
    : new ON_OBSOLETE_V2_DimRadial();
  V2_radial_dimension->Internal_InitializeFromV5Annotation(V5_linear_dimension,annotation_context);
  return V2_radial_dimension;
}

ON_OBSOLETE_V2_DimLinear* ON_OBSOLETE_V2_DimLinear::CreateFromV5LinearDimension(
  const class ON_OBSOLETE_V5_DimLinear& V5_linear_dimension,
  const ON_3dmAnnotationContext* annotation_context,
  ON_OBSOLETE_V2_DimLinear* destination
)
{
  ON_OBSOLETE_V2_DimLinear* V2_linear_dimension
    = (nullptr != destination)
    ? destination
    : new ON_OBSOLETE_V2_DimLinear();
  V2_linear_dimension->Internal_InitializeFromV5Annotation(V5_linear_dimension,annotation_context);
  return V2_linear_dimension;
}

ON_OBSOLETE_V5_DimLinear* ON_OBSOLETE_V5_DimLinear::CreateFromV2LinearDimension( 
  const class ON_OBSOLETE_V2_DimLinear& V2_linear_dimension,
  const ON_3dmAnnotationContext* annotation_context,
  ON_OBSOLETE_V5_DimLinear* destination
  )
{
  ON_OBSOLETE_V5_DimLinear* V5_linear_dimension
    = (nullptr != destination)
    ? destination
    : new ON_OBSOLETE_V5_DimLinear();

  V5_linear_dimension->Internal_InitializeFromV2Annotation(V2_linear_dimension,annotation_context);

  return V5_linear_dimension;
}

int ON_OBSOLETE_V5_DimLinear::GetDimensionLineSegments(
    ON_OBSOLETE_V5_RECT gdi_text_rect,
    int gdi_height_of_I,
    ON_Xform gdi_to_world,
    const ON_DimStyle& dimstyle,
    double dimscale,
    const ON_Viewport* vp,
    double x[6],
    bool& bInside
    ) const
{
  int rc = 0;

  x[0] = 0.0;
  x[1] = 0.0;
  x[2] = 0.0;
  x[3] = 0.0;
  x[4] = 0.0;
  x[5] = 0.0;
  bInside = true;

  if ( m_points.Count() < 3 )
    return 0;

  int i = (m_points[ext0_pt_index].x <= m_points[ext1_pt_index].x) 
      ? ext0_pt_index 
      : ext1_pt_index;
  const double x0 = m_points[i].x;
  const double x1 = m_points[(ext0_pt_index==i) ? ext1_pt_index : ext0_pt_index].x;
  x[0] = x0;  // left  end of first dimension line
  x[1] = x1;  // right end of first dimension line
  x[2] = x0;  // left  end of second dimension line
  x[3] = x1;  // right end of second dimension line
  x[4] = x0;  // tip of first arrow
  x[5] = x1;  // tip of second arrow

  if ( 0 == gdi_height_of_I )
  {
    // Default to height of Ariel 'I'
    gdi_height_of_I = (165*ON_Font::Constants::AnnotationFontCellHeight)/256;
  }

  if ( 0.0 == dimscale )
  {
    dimscale = 1.0;
  }

  double t;

  ON_INTERNAL_OBSOLETE::V5_TextDisplayMode textdisplay = ON_INTERNAL_OBSOLETE::V5TextDisplayModeFromV6DimStyle(dimstyle);

  const double text_height_of_I    = dimscale*dimstyle.TextHeight();
  const double textgap             = fabs(dimscale*dimstyle.TextGap());
  const double gdi_to_plane_scale  = text_height_of_I/gdi_height_of_I;
  const double textwidth           = fabs(gdi_to_plane_scale*(gdi_text_rect.right - gdi_text_rect.left));
  const double arrowwidth          = dimscale*dimstyle.ArrowSize();
  const double tailwidth           = 0.5*arrowwidth;
  const double dimwidth            = x1 - x0;
  const double mindimwidth         = (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine == textdisplay)
                                     ? (2.0*(arrowwidth + tailwidth + textgap) + textwidth)
                                   : (2.0*arrowwidth + tailwidth);
  const double dimextension        = dimscale*dimstyle.DimExtension();

  int ForceArrows = 0;
  const ON_OBSOLETE_V5_DimExtra* pDE = ON_OBSOLETE_V5_DimExtra::DimensionExtension(this,false);
  if( pDE)
    ForceArrows = pDE->ArrowPosition();

  // 19 Apr 2012 - Lowell - Fixed so forcing arrows inside won't cause the dim line to 
  // draw through InLine text  rr103322
  if(ForceArrows == -1 ||        // force outside
     (dimwidth < mindimwidth  && ForceArrows != 1))    // arrowheads have to be "outside" - they won't fit inside even without text
  {
    t = arrowwidth + tailwidth;
    x[0] = x0;
    x[1] = x0-t;
    x[2] = x1+t;
    x[3] = x1;
    x[4] = x0;  // arrow tips
    x[5] = x1;
    if( dimextension != 0.0)
    {
      x[0] += dimextension;
      x[3] -= dimextension;
    }
    bInside = false;
    rc = 2;
  }
  // Horizontal text or Userpositioned text
  else if ((ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen == textdisplay && vp) || m_userpositionedtext)
  {
    // use projected rectangle to clip dimension line
    double xx0, xx1, xx, y0, y1;
    ON_3dPoint P, R;
    ON_2dPoint corners[4];  // corners of text rect in plane coords
    ON_Line ray;

    ON_3dVector vp_zaxis = (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen == textdisplay && vp)
                         ? vp->CameraZ() 
                         : m_plane.zaxis;

    // 30 July 2012 - Lowell - Slightly shrink the text gap value
    // so that text + gap won't intersect the dim line if when text
    // is moved along the dim line. rr110504
    double gdi_gap = fabs(textgap/gdi_to_plane_scale)-12;
    if(gdi_gap < 0.0) gdi_gap = 0.0;

    R.Set(gdi_text_rect.left-gdi_gap,gdi_text_rect.bottom+gdi_gap,0.0);
    ray.from = gdi_to_world*R; ray.to = ray.from + vp_zaxis;
    P = ( ON_Intersect(ray,m_plane,&t) ) ? ray.PointAt(t) : ray.from;
    m_plane.ClosestPointTo(P,&corners[0].x,&corners[0].y);

    R.Set(gdi_text_rect.right+gdi_gap,gdi_text_rect.bottom+gdi_gap,0.0);
    ray.from = gdi_to_world*R; ray.to = ray.from + vp_zaxis;
    P = ( ON_Intersect(ray,m_plane,&t) ) ? ray.PointAt(t) : ray.from;
    m_plane.ClosestPointTo(P,&corners[1].x,&corners[1].y);

    R.Set(gdi_text_rect.right+gdi_gap,gdi_text_rect.top-gdi_gap,0.0);
    ray.from = gdi_to_world*R; ray.to = ray.from + vp_zaxis;
    P = ( ON_Intersect(ray,m_plane,&t) ) ? ray.PointAt(t) : ray.from;
    m_plane.ClosestPointTo(P,&corners[2].x,&corners[2].y);

    R.Set(gdi_text_rect.left-gdi_gap,gdi_text_rect.top-gdi_gap,0.0);
    ray.from = gdi_to_world*R; ray.to = ray.from + vp_zaxis;
    P = ( ON_Intersect(ray,m_plane,&t) ) ? ray.PointAt(t) : ray.from;
    m_plane.ClosestPointTo(P,&corners[3].x,&corners[3].y);

    // Test if text rect intersects dimension line
    xx0 = xx1 = ON_UNSET_VALUE;
    for ( i = 0; i < 4; i++ )
    {
      y0 = corners[i].y       - m_points[1].y;    // vertical dist from corner to dimension line
      y1 = corners[(i+1)%4].y - m_points[1].y;    // vertical dist from next corner to dimension line
      // if they're both above or both below, no intersection of this segment
      if ( (y0 > 0.0 && y1 > 0.0) || (y0 < 0.0 && y1 < 0.0) || y0 == y1 )
        continue;

      // segment intersects dimension line.
      // find x-coord of intersection
      t = y0/(y0-y1);
      xx = (1.0-t)*corners[i].x + t*corners[(i+1)%4].x;
      if ( ON_UNSET_VALUE == xx0 )
      {
        xx0 = xx1 = xx;
      }
      else if ( xx < xx0 )
      {
        xx0 = xx;
      }
      else if ( xx > xx1 )
      {
        xx1 = xx;
      }
    }

    // Nov 4 2009 - Lowell - Added test for no intersection of text with dimension line rr33003
    // Important for user positioned text that's moved out of the way of the dimension line
    if(xx0 != ON_UNSET_VALUE && xx1 != ON_UNSET_VALUE)
    {
      // xx0 is left edge of text rect
      // xx1 is right edge of text rect
      t = arrowwidth + tailwidth;
      if ( x0 + t <= xx0 && xx0 < xx1 && xx1 <= x1 - t )
      {
        // clip line, 2 segments arrows inside
        x[0] = x0;
        x[1] = xx0;
        x[2] = xx1;
        x[3] = x1;
        x[4] = x0;
        x[5] = x1;
        if( dimextension != 0.0)
        {
          x[0] -= dimextension;
          x[3] += dimextension;
        }
        rc = 2;
      }
      else  // 2 segments, put the arrows outside the extension lines
      {
        x[0] = x0;
        x[1] = x0 - t;
        x[2] = x1 + t;
        x[3] = x1;
        x[4] = x0;
        x[5] = x1;
        if( dimextension != 0.0)
        {
          x[0] += dimextension;
          x[3] -= dimextension;
        }
        bInside = false;
        rc = 2;
      }
    }
    else
    {
      // 1 segment, arrows inside
      x[0] = x0;
      x[1] = x1;
      x[2] = x0;
      x[3] = x1;
      x[4] = x0;
      x[5] = x1;
      if( dimextension != 0.0)
      {
        x[0] -= dimextension;
        x[1] += dimextension;
      }
      rc = 1;
    }
  }
  // Above line text
  else if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine == textdisplay || m_userpositionedtext)
  {
    // 1 segment, arrows inside
    x[0] = x0;
    x[1] = x1;
    x[2] = x0;
    x[3] = x1;
    x[4] = x0;
    x[5] = x1;
    if( dimextension != 0.0)
    {
      x[0] -= dimextension;
      x[1] += dimextension;
    }
    rc = 1;
  }
  // In line text
  else if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine == textdisplay)
  {
    // 2 segments, arrows inside
    t = 0.5*(dimwidth - textwidth - 2.0*textgap);
    x[0] = x0;
    x[1] = x0+t;
    x[2] = x1-t;
    x[3] = x1;
    x[4] = x0;
    x[5] = x1;
    if( dimextension != 0.0)
    {
      x[0] -= dimextension;
      x[3] += dimextension;
    }

    rc = 2;
  }

  return rc;
}


const wchar_t* ON_OBSOLETE_V5_DimLinear::DefaultText() { return L"<>"; }




//----- ON_OBSOLETE_V5_DimRadial ------------------------------------------
ON_OBSOLETE_V5_DimRadial::ON_OBSOLETE_V5_DimRadial()
{
  m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter;
  m_textdisplaymode = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine;
  SetTextValue(DefaultDiameterText());
  SetTextFormula(0);
  m_points.Reserve(ON_OBSOLETE_V5_DimRadial::dim_pt_count);
  m_points.SetCount(ON_OBSOLETE_V5_DimRadial::dim_pt_count);
  m_points.Zero();
}

ON_OBSOLETE_V5_DimRadial* ON_OBSOLETE_V5_DimRadial::CreateFromV2RadialDimension(
  const class ON_OBSOLETE_V2_DimRadial& V2_radial_dimension,
  const class ON_3dmAnnotationContext* annotation_context,
  ON_OBSOLETE_V5_DimRadial* destination
)
{
  ON_OBSOLETE_V5_DimRadial* V5_radial_dimension
    = (nullptr != destination)
    ? destination
    : new ON_OBSOLETE_V5_DimRadial();

  V5_radial_dimension->Internal_InitializeFromV2Annotation(V2_radial_dimension,annotation_context);

  return V5_radial_dimension;
}


bool ON_OBSOLETE_V5_DimRadial::IsValid( ON_TextLog* text_log ) const
{
  if ( m_type != ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius && m_type != ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter  )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimRadial - m_type !=  ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius or ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter\n");
    }
    return false;
  }

  if ( !ON_OBSOLETE_V5_Annotation::IsValid( text_log ))
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimRadial - invalid ON_OBSOLETE_V5_Annotation base class.\n");
    }
    return false;
  }

  if ( 4 != m_points.Count() )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimRadial - m_points.Count() = %d (should be 4 or 5)\n", m_points.Count() );
    }
    return false;
  }

  return true;
}


bool ON_OBSOLETE_V5_DimRadial::Write(ON_BinaryArchive& archive) const
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_DimRadial
  //    V4 did not have a ON_OBSOLETE_V5_DimRadial::Write and simply called
  //    ON_OBSOLETE_V5_Annotation::Write.
  bool rc = false;
  bool bInChunk = (archive.Archive3dmVersion() >= 5);
  if ( bInChunk )
  {
    rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Write(archive)?true:false;
    if (!rc) break;
    if ( !bInChunk )
      break;

    // To write new fields, increment minor version number
    // and write values here.  Ask Dale Lear for help.

    break;
  }

  if ( bInChunk )
  {
    if (!archive.EndWrite3dmChunk())
      rc = false;
  }
  return rc;
}

bool ON_OBSOLETE_V5_DimRadial::Read(ON_BinaryArchive& archive)
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_DimRadial
  int major_version = 0;
  int minor_version = 0;
  bool rc = false;
  bool bInChunk = (archive.Archive3dmVersion() >= 5 && archive.ArchiveOpenNURBSVersion() >= 200710180);
  if ( bInChunk )
  {
    rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Read(archive)?true:false;
    if (!rc) break;
    if ( !bInChunk || minor_version <= 0 )
      break;

    // read future addition here

    break;
  }

  if ( bInChunk )
  {
    if ( !archive.EndRead3dmChunk() )
      rc = false;
  }
  return rc;
}


bool ON_OBSOLETE_V5_DimRadial::GetBBox(
        double* boxmin,
        double* boxmax,
        bool bGrowBox
        ) const
{
  ON_BoundingBox bbox;
  if ( bGrowBox )
  {
    bbox.m_min.x = boxmin[0]; 
    bbox.m_min.y = boxmin[1]; 
    bbox.m_min.z = boxmin[2];
    bbox.m_max.x = boxmax[0]; 
    bbox.m_max.y = boxmax[1]; 
    bbox.m_max.z = boxmax[2];
    if ( !bbox.IsValid() )
    {
      bbox.Destroy();
      bGrowBox = false;
    }
  }

  if ( 4 == m_points.Count() )
  {
    ON_3dPointArray P(4);
    ON_2dPoint uv;
    if ( m_userpositionedtext )
    {
      uv = m_points[0]; // point someplace in text
      P.Append( m_plane.PointAt(uv.x,uv.y) );
    }

    P.Append( m_plane.origin ); // + sign at center of dimension

    uv = m_points[1];
    P.Append( m_plane.PointAt(uv.x,uv.y) );

    uv = m_points[2];
    P.Append( m_plane.PointAt(uv.x,uv.y) );

    uv = m_points[3];
    P.Append( m_plane.PointAt(uv.x,uv.y) );
    bGrowBox = P.GetBBox(&bbox.m_min.x, &bbox.m_max.x, bGrowBox);
  }

  if ( bGrowBox )
  {
    boxmin[0] = bbox.m_min.x; 
    boxmin[1] = bbox.m_min.y; 
    boxmin[2] = bbox.m_min.z; 
    boxmax[0] = bbox.m_max.x; 
    boxmax[1] = bbox.m_max.y; 
    boxmax[2] = bbox.m_max.z; 
  }

  return bGrowBox;
}

bool ON_OBSOLETE_V5_DimRadial::GetTightBoundingBox( 
		ON_BoundingBox& tight_bbox, 
    bool bGrowBox,
		const ON_Xform* xform
    ) const
{
  if ( 4 == m_points.Count() )
  {
    ON_3dPointArray P(4);
    for(int i = 0; i < 4; i++)
      P.Append( m_plane.PointAt(m_points[i].x,m_points[i].y) );

    if ( P.GetTightBoundingBox( tight_bbox, bGrowBox, xform ) )
      bGrowBox = true;
  }
  else if ( bGrowBox && !tight_bbox.IsValid() )
  {
    tight_bbox.Destroy();
    bGrowBox = false;
  }

  return (0!=bGrowBox);
}

ON_2dPoint ON_OBSOLETE_V5_DimRadial::Dim2dPoint(
      int point_index
      ) const
{
  ON_2dPoint p2;
  if ( m_points.Count() < dim_pt_count || point_index < 0 )
  {
    p2.x = p2.y = ON_UNSET_VALUE;
  }
  else
  {
    if ( text_pivot_pt == point_index )
    {
      point_index = tail_pt_index;
    }
    if ( point_index < dim_pt_count )
    {
      p2 = m_points[point_index];
    }    
    else
    {
      p2.x = p2.y = ON_UNSET_VALUE;
    }
  }
  return p2;
}

ON_3dPoint ON_OBSOLETE_V5_DimRadial::Dim3dPoint(
      int point_index
      ) const
{
  ON_2dPoint p2 = Dim2dPoint(point_index);
  return (ON_UNSET_VALUE == p2.x) ? ON_3dPoint::UnsetPoint : m_plane.PointAt(p2.x,p2.y);
}

// set the plane, center, and point on curve.
// the rest will be set by the Rhino dimension
bool ON_OBSOLETE_V5_DimRadial::CreateFromPoints( 
  ON_3dPoint center, 
  ON_3dPoint arrowtip, 
  ON_3dVector xaxis, 
  ON_3dVector normal,
  double offset_distance)
{
  if ( m_type != ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter )
    m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius;
  bool rc = false;
  if ( center.IsValid() && arrowtip.IsValid() && normal.IsValid() && !normal.IsZero() && xaxis.IsValid() && !xaxis.IsZero() )
  {
    ON_Plane plane( center, normal);
    double c = xaxis*plane.xaxis;
    double s = xaxis*plane.yaxis;
    if ( c != 0.0 || s != 0.0 )
    {
      if ( c <= 0.0 || s != 0.0 )
      {
        plane.Rotate( s, c, plane.zaxis );
      }
      m_plane = plane;
      ON_2dVector tip;
      if ( m_plane.ClosestPointTo(arrowtip,&tip.x,&tip.y) )
      {
        //double r = tip.Length();
        m_points.SetCapacity(dim_pt_count);
        m_points.SetCount(dim_pt_count);

        m_points[center_pt_index].Set(0.0,0.0);
        m_points[arrow_pt_index] = tip;
        tip.Unitize();

        m_points[knee_pt_index] = m_points[arrow_pt_index] + offset_distance*tip;
        m_points[tail_pt_index] = m_points[knee_pt_index];
        if ( m_points[arrow_pt_index].x < 0.0 )
          m_points[tail_pt_index].x -= offset_distance;
        else
          m_points[tail_pt_index].x += offset_distance;
        m_plane = plane;
        m_userpositionedtext = false;

        rc = true;
      }
    }
  }
  return rc;
}


double ON_OBSOLETE_V5_DimRadial::NumericValue() const
{
  double d = 0.0;
  if ( m_points.Count() >= dim_pt_count )
  {
    d = (m_points[center_pt_index] - m_points[arrow_pt_index]).Length();
    if( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter == m_type )
      d *= 2.0;
  }
  return d;
}

int ON_OBSOLETE_V5_DimRadial::StyleIndex() const
{
  return ON_OBSOLETE_V5_Annotation::V5_3dmArchiveDimStyleIndex();
}

void ON_OBSOLETE_V5_DimRadial::SetStyleIndex( int i)
{
  ON_OBSOLETE_V5_Annotation::SetV5_3dmArchiveDimStyleIndex( i);
}


const wchar_t* ON_OBSOLETE_V5_DimRadial::DefaultRadiusText()
{
  static wchar_t defstr[4] = { ON_wString::RadiusSymbol, L'<', L'>', 0 };
  return defstr;
}

const wchar_t* ON_OBSOLETE_V5_DimRadial::DefaultDiameterText()
{
  static wchar_t defstr[4] = { ON_wString::DiameterSymbol, L'<', L'>', 0 };
  return defstr;
}


bool ON_OBSOLETE_V5_DimRadial::CreateFromV2( 
    const ON_OBSOLETE_V2_Annotation& v2_ann,
    const ON_3dmAnnotationSettings& settings,
    int dimstyle_index
    )
{
  bool rc = false;
  if( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius == v2_ann.m_type || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter == v2_ann.m_type )
  {
    const ON_SimpleArray<ON_2dPoint>& points = v2_ann.Points();
    if ( points.Count() >= 4 )
    {
      m_points.Reserve(4);
      m_points.SetCount(0);
      m_points.Append(4,points.Array());
      m_plane = v2_ann.m_plane;
      m_plane.UpdateEquation();
      SetTextValue(static_cast< const wchar_t* >(v2_ann.UserText()));
      SetTextFormula(0);
      m_userpositionedtext = false;
      m_type = v2_ann.Type();
      m_textdisplaymode = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine;
      SetV5_3dmArchiveDimStyleIndex(dimstyle_index);
      ON_2dVector v = m_points[0];
      if ( !v.IsZero() )
      {
        m_plane.origin = m_plane.PointAt(v.x,v.y);
        m_plane.UpdateEquation();
        v = -v;
        m_points[0].Set(0.0,0.0);
        m_points[1] += v;
        m_points[2] += v;
        m_points[3] += v;
      }

      rc = true;
    }
  }
  return rc;
}


//----- ON_AngularDimension2Extra -----------------------------------------
// Additions to ON_OBSOLETE_V5_DimAngular class

class ON_AngularDimension2Extra : public ON_UserData
{
  ON_OBJECT_DECLARE(ON_AngularDimension2Extra);
public:
  static ON_AngularDimension2Extra* AngularDimensionExtra(ON_OBSOLETE_V5_DimAngular* pDim/*, bool bCreate*/);
  static const ON_AngularDimension2Extra* AngularDimensionExtra(const ON_OBSOLETE_V5_DimAngular* pDim/*, bool bCreate*/);

  ON_AngularDimension2Extra();
  ~ON_AngularDimension2Extra();

  // override virtual ON_Object::Dump function
  void Dump( ON_TextLog& text_log ) const override;

  // override virtual ON_Object::SizeOf function
  unsigned int SizeOf() const override;

  // override virtual ON_Object::Write function
  bool Write(ON_BinaryArchive& binary_archive) const override;

  // override virtual ON_Object::Read function
  bool Read(ON_BinaryArchive& binary_archive) override;

  // override virtual ON_UserData::GetDescription function
  bool GetDescription( ON_wString& description ) override;

  // override virtual ON_UserData::Archive function
  bool Archive() const override;

  // Scale all of the length values
  void Scale( double scale);

  // 
  double DimpointOffset(int index) const;
  void SetDimpointOffset(int index, double offset);

  // offsets from apex of dimension to point from which extension lines start
  // if these are < 0.0, they are ignored
  // Extension lines are drawn from theses points to the Arrow tip points
  // subject to dimexe & dimexo & dimse1 & dimse2
  double m_dimpoint_offset[2];
};

ON_OBJECT_IMPLEMENT(ON_AngularDimension2Extra,ON_UserData,"A68B151F-C778-4a6e-BCB4-23DDD1835677");

ON_AngularDimension2Extra* ON_AngularDimension2Extra::AngularDimensionExtra(ON_OBSOLETE_V5_DimAngular* pDim)
{
  ON_AngularDimension2Extra* pExtra = 0;
  if(pDim)
  {
    pExtra = ON_AngularDimension2Extra::Cast(pDim->GetUserData(ON_CLASS_ID(ON_AngularDimension2Extra)));
    if(pExtra == 0)
    {
      pExtra = new ON_AngularDimension2Extra;
      if( pExtra)
      {
        if(!pDim->AttachUserData(pExtra))
        {
          delete pExtra;
          pExtra = 0;
        }
      }
    }
  }
  return pExtra;
}

const ON_AngularDimension2Extra* ON_AngularDimension2Extra::AngularDimensionExtra(const ON_OBSOLETE_V5_DimAngular* pDim)
{
  return AngularDimensionExtra((ON_OBSOLETE_V5_DimAngular*)pDim);
}

ON_AngularDimension2Extra::ON_AngularDimension2Extra()
{
  m_userdata_uuid = ON_CLASS_ID(ON_AngularDimension2Extra);
  m_application_uuid = ON_opennurbs5_id; // opennurbs.dll reads/writes this userdata
                                         // The id must be the version 5 id because
                                         // V6 SaveAs V5 needs to work, but SaveAs
                                         // V4 should not write this userdata.
  m_userdata_copycount = 1;

  m_dimpoint_offset[0] = 0;
  m_dimpoint_offset[1] = 0;
}

ON_AngularDimension2Extra::~ON_AngularDimension2Extra()
{
}

void ON_AngularDimension2Extra::Dump( ON_TextLog& text_log ) const
{
  // do nothing
}

unsigned int ON_AngularDimension2Extra::SizeOf() const
{
  unsigned int sz = ON_UserData::SizeOf();
  sz += sizeof(*this) - sizeof(ON_UserData);
  return sz;
}

bool ON_AngularDimension2Extra::Write(ON_BinaryArchive& archive) const
{
  int major_version = 1;
  int minor_version = 0;
  bool rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,major_version,minor_version);

  if(rc) rc = archive.WriteDouble(m_dimpoint_offset[0]);
  if(rc) rc = archive.WriteDouble(m_dimpoint_offset[1]);

  if(!archive.EndWrite3dmChunk())
    rc = false;

  return rc;
}

bool ON_AngularDimension2Extra::Read(ON_BinaryArchive& archive)
{
  int major_version = 1;
  int minor_version = 0;
  bool rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if(major_version != 1)
    rc = false;

  if(rc) rc = archive.ReadDouble(&m_dimpoint_offset[0]);
  if(rc) rc = archive.ReadDouble(&m_dimpoint_offset[1]);

  if ( !archive.EndRead3dmChunk() )
    rc = false;

  return rc;
}

bool ON_AngularDimension2Extra::GetDescription( ON_wString& description)
{
  description = L"Userdata extension of ON_OBSOLETE_V5_DimAngular";
  return true;
}

bool ON_AngularDimension2Extra::Archive() const
{
  // true to write to file
  return true;
}

void ON_AngularDimension2Extra::Scale(double scale)
{
  if( ON_IsValid(scale) && scale > ON_SQRT_EPSILON)
  {
    m_dimpoint_offset[0] *= scale;
    m_dimpoint_offset[1] *= scale;
  }
}

double ON_AngularDimension2Extra::DimpointOffset(int index) const
{
  if(index == 0)
    return m_dimpoint_offset[0];
  if(index == 1)
    return m_dimpoint_offset[1];
  return -1;
}
void ON_AngularDimension2Extra::SetDimpointOffset(int index, double offset)
{
  if(index >= 0 && index <= 1)
    m_dimpoint_offset[index] = offset;
}

//----- ON_OBSOLETE_V5_DimAngular -----------------------------------------
ON_OBSOLETE_V5_DimAngular::ON_OBSOLETE_V5_DimAngular()
  : m_angle(0.0)
  , m_radius(1.0)
{
  m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular;
  m_textdisplaymode = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine;
  SetTextValue(DefaultText());
  SetTextFormula(0);
  m_points.Reserve(ON_OBSOLETE_V5_DimAngular::dim_pt_count);
  m_points.SetCount(ON_OBSOLETE_V5_DimAngular::dim_pt_count);
  m_points.Zero();
}

ON_OBSOLETE_V5_DimAngular* ON_OBSOLETE_V5_DimAngular::CreateFromV2AngularDimension(
  const class ON_OBSOLETE_V2_DimAngular& V2_angular_dimension,
  const class ON_3dmAnnotationContext* annotation_context,
  ON_OBSOLETE_V5_DimAngular* destination
)
{
  ON_OBSOLETE_V5_DimAngular* V5_angular_dimension
    = (nullptr != destination)
    ? destination
    : new ON_OBSOLETE_V5_DimAngular();

  V5_angular_dimension->Internal_InitializeFromV2Annotation(V2_angular_dimension,annotation_context);

  ON_2dVector v0 // point on first line
    = (V2_angular_dimension.m_points.Count() >= 2 && V2_angular_dimension.m_points[0].IsValid())
    ? (V2_angular_dimension.m_points[0] - ON_2dPoint::Origin)
    : ON_2dVector::ZeroVector;
  ON_2dVector v1 // point on second line
    = (V2_angular_dimension.m_points.Count() >= 2 && V2_angular_dimension.m_points[1].IsValid())
    ? (V2_angular_dimension.m_points[1] - ON_2dPoint::Origin)
    : ON_2dVector::ZeroVector;
  ON_2dPoint tp // point on second line
    = (V2_angular_dimension.m_points.Count() >= 3 && V2_angular_dimension.m_points[2].IsValid())
    ? V2_angular_dimension.m_points[2]
    : ON_2dPoint::UnsetPoint;
  double angle = V2_angular_dimension.Radius();
  double radius = V2_angular_dimension.Angle();

  bool bUserPositionedText = (v0.IsNotZero() && v1.IsNotZero() && V5_angular_dimension->m_userpositionedtext && tp.IsValid());
  V5_angular_dimension->m_userpositionedtext = bUserPositionedText;

  if (v0.IsNotZero() && v1.IsNotZero())
  {
    ON_Plane plane = V5_angular_dimension->m_plane;
    for (;;)
    {
      if (v0.x > 0.0 && 0.0 == v0.y)
        break;
      bUserPositionedText = false;
      const double length0 = v0.Length();
      if (!(length0 > 0.0))
        break;
      const ON_3dPoint P0 = plane.PointAt(v0.x, v0.y);
      if (!P0.IsValid())
        break;
      const ON_3dPoint P1 = plane.PointAt(v1.x, v1.y);
      if (!P1.IsValid())
        break;
      plane.xaxis = P0 - plane.origin;
      if (!plane.xaxis.Unitize())
        break;
      plane.yaxis = ON_CrossProduct(plane.zaxis, plane.xaxis);
      if (!plane.yaxis.Unitize())
        break;
      if (!plane.IsValid())
        break;
      ON_2dVector v = v1;
      if (!plane.ClosestPointTo(P1, &v.x, &v.y))
        break;
      v0.x = length0;
      v0.y = 0.0;
      v1 = v;
      V5_angular_dimension->m_plane = plane;
      angle = atan2(v1.y,v1.x);
      if ( angle < 0.0 )
        angle += 2.0*ON_PI;
      radius = 0.5*(v0.Length() + v1.Length());
      break;
    }
  }

  if ( !bUserPositionedText )
  {
    tp.x = radius*cos(0.5*angle);
    tp.y = radius*sin(0.5*angle);
  }

  const ON_2dPoint arcpt( radius*cos(angle/3.0), radius*sin(angle/3.0) );

  V5_angular_dimension->m_points.SetCapacity(4);
  V5_angular_dimension->m_points.SetCount(4);
  V5_angular_dimension->m_points[0] = tp.IsValid() ? tp : ON_2dPoint::Origin;
  V5_angular_dimension->m_points[1] = (v0.IsValid() && v0.IsNotZero()) ? ON_2dPoint(v0) : ON_2dPoint::Origin;
  V5_angular_dimension->m_points[2] = (v1.IsValid() && v1.IsNotZero()) ? ON_2dPoint(v1) : ON_2dPoint::Origin;
  V5_angular_dimension->m_points[3] = arcpt.IsValid() ? arcpt : ON_2dPoint::Origin;
  V5_angular_dimension->m_angle = angle;
  V5_angular_dimension->m_radius = radius;

  V5_angular_dimension->m_userpositionedtext = bUserPositionedText;

  return V5_angular_dimension;
}


bool ON_OBSOLETE_V5_DimAngular::IsValid( ON_TextLog* text_log ) const
{
  if ( m_type != ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - m_type !=  ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular\n");
    }
    return false;
  }

  if ( !ON_OBSOLETE_V5_Annotation::IsValid( text_log ))
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - invalid ON_OBSOLETE_V5_Annotation base class.\n");
    }
    return false;
  }

  if ( 4 != m_points.Count() )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - m_points.Count() = %d (should be 4)\n", m_points.Count() );
    }
    return false;
  }

  if ( !ON_IsValid(m_angle) || m_angle <= 0.0 || m_angle > 2.0*ON_PI )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - bogus m_angle = %g\n",m_angle);
    }
    return false;
  }

  if ( !ON_IsValid(m_radius) || m_radius <= 0.0 )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - bogus m_radius = %g\n",m_radius);
    }
    return false;
  }

  if ( 0.0 == m_points[1].x && 0.0 == m_points[1].y )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - angle dim m_points[1] = center (should be on start ray).\n");
    }
    return false;
  }

  if ( 0.0 == m_points[2].x && 0.0 == m_points[2].y )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - angle dim m_points[2] = center (should be on end ray).\n");
    }
    return false;
  }

  if ( 0.0 == m_points[3].x && 0.0 == m_points[3].y )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - angle dim m_points[3] = center (should be on interior of arc).\n");
    }
    return false;
  }

  double a1 = atan2(m_points[1].y, m_points[1].x);
  double a2 = atan2(m_points[2].y, m_points[2].x);
  double a3 = atan2(m_points[3].y, m_points[3].x);
  if ( a1 < 0.0 )
    a1 += 2.0*ON_PI;
  while ( a2 <= a1 )
    a2 += 2.0*ON_PI;
  while ( a3 < a1 )  // Oct 23 2009 LW changed from a3 <= a1 to allow point at end of arc rr53634
    a3 += 2.0*ON_PI;

  if ( fabs(m_angle - (a2-a1)) > ON_ZERO_TOLERANCE + m_angle*ON_SQRT_EPSILON )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - m_angle = %g != %g = (end angle - start angle)\n",m_angle,a2-a1);
    }
    return false;
  }

  double r = ON_2dVector(m_points[3]).Length();
  if ( fabs(r - m_radius) > ON_ZERO_TOLERANCE + m_radius*ON_SQRT_EPSILON )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - m_radius = %g != %g = |m_point[3])|\n",m_radius,r);
    }
    return false;
  }
  

  if ( a3 > a2 )  // Oct 23 2009 LW changed from a3 >= a2 to allow point at end of arc rr53634
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimAngular - angle dim m_points[3] = not on arc interior.\n");
    }
    return false;
  }

  return true;
}



bool ON_OBSOLETE_V5_DimAngular::GetBBox(
        double* boxmin,
        double* boxmax,
        bool bGrowBox
        ) const
{
  ON_BoundingBox bbox;
  if ( bGrowBox )
  {
    bbox.m_min.x = boxmin[0]; 
    bbox.m_min.y = boxmin[1]; 
    bbox.m_min.z = boxmin[2];
    bbox.m_max.x = boxmax[0]; 
    bbox.m_max.y = boxmax[1]; 
    bbox.m_max.z = boxmax[2];
    if ( !bbox.IsValid() )
    {
      bbox.Destroy();
      bGrowBox = false;
    }
  }

  ON_Arc arc;
  if ( GetArc(arc) )
  {
    if ( arc.GetTightBoundingBox(bbox,bGrowBox?true:false,0) )
      bGrowBox = true;    
  }

  if ( bGrowBox )
  {
    boxmin[0] = bbox.m_min.x; 
    boxmin[1] = bbox.m_min.y; 
    boxmin[2] = bbox.m_min.z; 
    boxmax[0] = bbox.m_max.x; 
    boxmax[1] = bbox.m_max.y; 
    boxmax[2] = bbox.m_max.z; 
  }

  return bGrowBox;
}





bool ON_OBSOLETE_V5_DimAngular::GetTightBoundingBox( 
		ON_BoundingBox& tight_bbox, 
    bool bGrowBox,
		const ON_Xform* xform
    ) const
{
  ON_Arc arc;
  if ( GetArc(arc) )
  {
    if ( arc.GetTightBoundingBox(tight_bbox,bGrowBox,xform) )
      bGrowBox = true;    
  }
  else if ( bGrowBox && !tight_bbox.IsValid() )
  {
    tight_bbox.Destroy();
    bGrowBox = false;
  }

  return (0!=bGrowBox);

}

ON_2dPoint ON_OBSOLETE_V5_DimAngular::Dim2dPoint( int point_index ) const
{
  ON_2dPoint p2;
  if ( m_points.Count() < dim_pt_count || point_index < 0 )
  {
    p2.x = p2.y = ON_UNSET_VALUE;
  }
  else
  {
    if ( text_pivot_pt == point_index )
    {
      point_index = m_userpositionedtext 
                  ? userpositionedtext_pt_index
                  : arcmid_pt;
    }
    
    if ( point_index < dim_pt_count )
    {
      p2 = m_points[point_index];
    }
    else
    {
      switch(point_index)
      {
      case arcstart_pt:
        p2.x = m_radius;
        p2.y = 0.0;
        break;
      case arcend_pt:
        p2.x = m_radius*cos(m_angle);
        p2.y = m_radius*sin(m_angle);
        break;
      case arccenter_pt:
        p2.x = 0.0;
        p2.y = 0.0;
        break;
      case arcmid_pt:
        p2.x = m_radius*cos(0.5*m_angle);
        p2.y = m_radius*sin(0.5*m_angle);
        break;
      case extension0_pt:
        {
          p2 = m_points[start_pt_index];
          double dp0 = DimpointOffset(0);
          if(dp0 >= 0)
          {
            ON_2dVector v2 = (ON_2dVector)p2;
            v2.Unitize();
            p2 = (ON_2dPoint)v2 * dp0;
          }
        }
        break;
      case extension1_pt:
        {
          p2 = m_points[end_pt_index];
          double dp1 = DimpointOffset(1);
          if(dp1 >= 0)
          {
            ON_2dVector v2 = (ON_2dVector)p2;
            v2.Unitize();
            p2 = (ON_2dPoint)v2 * dp1;
          }
        }
        break;
      default:
        p2.x = p2.y = ON_UNSET_VALUE;
        break;
      }
    }
  }
  return p2;
}

ON_3dPoint ON_OBSOLETE_V5_DimAngular::Dim3dPoint( int point_index ) const
{
  ON_2dPoint p2 = Dim2dPoint(point_index);
  if (ON_UNSET_VALUE == p2.x)
    return ON_3dPoint::UnsetPoint;

  ON_3dPoint p = m_plane.PointAt(p2.x, p2.y);
  return p;

  //return (ON_UNSET_VALUE == p2.x) ? ON_3dPoint::UnsetPoint : m_plane.PointAt(p2.x,p2.y);
}


bool ON_OBSOLETE_V5_DimAngular::Write( ON_BinaryArchive& file ) const
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_DimLinear
  //    V4 did not have a ON_OBSOLETE_V5_DimLinear::Write and simply called
  //    ON_OBSOLETE_V5_Annotation::Write.
  bool rc = false;
  bool bInChunk = (file.Archive3dmVersion() >= 5);
  if ( bInChunk )
  {
    rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Write(file)?true:false;
    if (!rc) break;
    rc = file.WriteDouble( m_angle);
    if (!rc) break;
    rc = file.WriteDouble( m_radius);
    if (!rc) break;
    if ( !bInChunk )
      break;

    // to write new V5 fields, increment the minor
    // version number and write them below

    break;
  }

  if ( bInChunk )
  {
    if (!file.EndWrite3dmChunk())
      rc = false;
  }

  return rc;
}

bool ON_OBSOLETE_V5_DimAngular::Read( ON_BinaryArchive& file )
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_DimAngular
  int major_version = 0;
  int minor_version = 0;
  bool rc = false;
  bool bInChunk = (file.Archive3dmVersion() >= 5 && file.ArchiveOpenNURBSVersion() >= 200710180);
  if ( bInChunk )
  {
    rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Read(file)?true:false;
    if (!rc) break;
    rc = file.ReadDouble( &m_angle);
    if (!rc) break;
    rc = file.ReadDouble( &m_radius);
    if (!rc) break;
    if ( !bInChunk || minor_version <= 0 )
      break;

    // Code to read any new ON_OBSOLETE_V5_DimAngular fields will 
    // go here.

    break;
  }

  if ( bInChunk )
  {
    // To read new ON_OBSOLETE_V5_DimAngular specific additions,
    // examine the minor version number and read the information
    // here.  Please ask Dale Lear for help.

    if ( !file.EndRead3dmChunk() )
      rc = false;
  }
  return rc;
}

static bool VectorAngle( const ON_2dVector& v, double& angle)
{
  if( v.IsTiny())
    return false;

  angle = atan2( v.y, v.x);

  if( angle < 0.0)
    angle += 2.0 * ON_PI;

  if( angle > 2.0 * ON_PI)
    angle -= 2.0 * ON_PI;

  return true;
}

bool ON_OBSOLETE_V5_DimAngular::CreateFromArc( const ON_Arc& arc )
{
  // June 9, 2010 - Lowell - Changed to call CreateFromPoints()
  bool rc = arc.IsValid();
  if (rc)
  {
    ON_3dPoint C = arc.Center();
    ON_3dPoint S = arc.StartPoint();
    ON_3dPoint E = arc.EndPoint();
    ON_3dPoint M = arc.MidPoint();
    ON_3dVector N = arc.Plane().zaxis;

    rc = CreateFromPoints(C, S, E, M, N);
  }

  return rc;
}

bool ON_OBSOLETE_V5_DimAngular::GetArc( ON_Arc& arc ) const
{
  bool rc = false;
  // Jan 25, 2007 - changed min radius from >0 to >ON_SQRT_EPSILON
  // to avoid domain problems trying to use very small arcs later
  if ( ON_IsValid(m_radius) && m_radius > ON_SQRT_EPSILON
      && ON_IsValid(m_angle) && m_angle > 0.0 && m_angle <= 2.0*ON_PI
      && m_plane.origin.IsValid() 
      && m_plane.xaxis.IsValid() 
      && m_plane.yaxis.IsValid() 
      && m_plane.zaxis.IsValid()
      && fabs( m_plane.zaxis.Length() - 1.0 ) <= ON_SQRT_EPSILON
      && 4 == m_points.Count()
      )
  {
    ON_3dVector X = m_plane.PointAt( m_points[start_pt_index].x, m_points[start_pt_index].y ) - m_plane.origin;
    if ( fabs(X.Length()-1.0) <= ON_SQRT_EPSILON || X.Unitize() )
    {
      if ( fabs(X*m_plane.zaxis) <= ON_SQRT_EPSILON )
      {
        ON_3dVector Y = ON_CrossProduct( m_plane.zaxis, X );
        if ( fabs(Y.Length()-1.0) <= ON_SQRT_EPSILON || Y.Unitize() )
        {
          arc.plane = m_plane;
          arc.plane.xaxis = X;
          arc.plane.yaxis = Y;
          arc.plane.UpdateEquation();
          arc.SetAngleIntervalRadians( ON_Interval(0.0,m_angle) );
          arc.radius = m_radius;
          rc = true;
        }
      }
    }
  }

  return rc;
}

bool ON_OBSOLETE_V5_DimAngular::GetExtensionLines(ON_Line extensions[2]) const
{
  bool rc = false;

  if ( ON_IsValid(m_radius) && m_radius > ON_SQRT_EPSILON
      && ON_IsValid(m_angle) && m_angle > 0.0 && m_angle <= 2.0*ON_PI
      && m_plane.origin.IsValid() 
      && m_plane.xaxis.IsValid() 
      && m_plane.yaxis.IsValid() 
      && m_plane.zaxis.IsValid()
      && fabs( m_plane.zaxis.Length() - 1.0 ) <= ON_SQRT_EPSILON
      && 4 == m_points.Count()
      )
  {
    const ON_AngularDimension2Extra* pDE = ON_AngularDimension2Extra::AngularDimensionExtra(this);
    if(pDE != 0)
    {
      double exoffset0 = pDE->DimpointOffset(0);
      double exoffset1 = pDE->DimpointOffset(1);
      ON_3dPoint e00, e01, e10, e11;
      e00 = m_plane.PointAt(m_points[start_pt_index].x, m_points[start_pt_index].y);
      e10 = m_plane.PointAt(m_points[end_pt_index].x, m_points[end_pt_index].y);
      ON_3dVector X = e00 - m_plane.origin;
      ON_3dVector Y = e10 - m_plane.origin;
      if((fabs(X.Length()-1.0) <= ON_SQRT_EPSILON || X.Unitize()) &&
         (fabs(Y.Length()-1.0) <= ON_SQRT_EPSILON || Y.Unitize()))
      {
        if((fabs(X*m_plane.zaxis) <= ON_SQRT_EPSILON) &&
           (fabs(Y*m_plane.zaxis) <= ON_SQRT_EPSILON))
        {
          e00 = m_plane.origin + X * exoffset0;
          e10 = m_plane.origin + Y * exoffset1;
          e01 = m_plane.origin + X * m_radius;
          e11 = m_plane.origin + Y * m_radius;

          extensions[0].from = e00;
          extensions[0].to   = e01;
          extensions[1].from = e10;
          extensions[1].to   = e11;
          rc = true;
        }
      }
    }
  }
  return rc;
}


bool ON_OBSOLETE_V5_DimAngular::CreateFromPoints( 
            const ON_3dPoint& pc, 
            const ON_3dPoint& p0in,
            const ON_3dPoint& p1in,
            ON_3dPoint& arcpt, 
            ON_3dVector& Normal)
{
  ON_3dPoint p0, p1;
  p0 = p0in;
  p1 = p1in;

  ON_Plane plane( pc, Normal);

  ON_2dPoint pa, pp0, pp1;

  if( !plane.ClosestPointTo( p0, &pp0.x, &pp0.y))
    return false;

  // rotate so that p0 is on x-axis
  ON_2dVector v0( pp0);
  v0.Unitize();
  if ( v0.IsValid() && v0.IsNotZero() )
    plane.Rotate( v0.y, v0.x, plane.Normal());

  if( !plane.ClosestPointTo( p0, &pp0.x, &pp0.y))
    return false;

  if( !plane.ClosestPointTo( arcpt, &pa.x, &pa.y))
    return false;

  if( !plane.ClosestPointTo( p1, &pp1.x, &pp1.y))
    return false;

  double a1 = ON_DBL_QNAN;
  double aa = ON_DBL_QNAN;
  if( !VectorAngle( ON_2dVector( pp1), a1) || !VectorAngle( ON_2dVector( pa), aa))    
    return false;

  if( aa > a1)  // the angle is really the bigger one ( > 180)
  {
    // rotate so that p0 is on x-axis
    v0.Set( pp1.x, pp1.y);
    v0.Unitize();
    plane.Rotate( v0.y, v0.x, plane.Normal());

    if( !plane.ClosestPointTo( arcpt, &pa.x, &pa.y))
      return false;
    if( !plane.ClosestPointTo( p1, &pp0.x, &pp0.y))
      return false;
    if( !plane.ClosestPointTo( p0, &pp1.x, &pp1.y))
      return false;
  }

  VectorAngle( ON_2dVector( pp1), a1);

  SetAngle( a1);
  SetRadius( ON_2dVector( pa).Length());

  ON_AngularDimension2Extra* pDE = ON_AngularDimension2Extra::AngularDimensionExtra(this);
  if(pDE != 0)
  {
    double os = ((ON_2dVector)pp0).Length();
    pDE->SetDimpointOffset(0, os);
    os = ((ON_2dVector)pp1).Length();
    pDE->SetDimpointOffset(1, os);
  }

  ReservePoints( 4);
  SetPlane( plane);
  SetPoint( 1, pp0);
  SetPoint( 2, pp1);
  SetPoint( 3, pa);


  return true;
}

void ON_OBSOLETE_V5_DimAngular::SetAngle( double angle)
{
  m_angle = angle;
}

double ON_OBSOLETE_V5_DimAngular::Angle() const
{
  return m_angle;
}

void ON_OBSOLETE_V5_DimAngular::SetRadius( double radius)
{
  m_radius = radius;
}

double ON_OBSOLETE_V5_DimAngular::Radius() const
{
  return m_radius;
}

double ON_OBSOLETE_V5_DimAngular::NumericValue() const
{
  // This returns degrees - if we get another angular unit system, add it
  return (m_angle*180.0/ON_PI);
}

int ON_OBSOLETE_V5_DimAngular::StyleIndex() const
{
  return ON_OBSOLETE_V5_Annotation::V5_3dmArchiveDimStyleIndex();
}

void ON_OBSOLETE_V5_DimAngular::SetStyleIndex( int i)
{
  ON_OBSOLETE_V5_Annotation::SetV5_3dmArchiveDimStyleIndex( i);
}

const wchar_t* ON_OBSOLETE_V5_DimAngular::DefaultText()
{
  return L"<>"; // Aug 31, 2009 - Lowell
}





static void OrientRectHelper( ON_2dVector corners[4] )
{
  double twice_area = 0.0;
  ON_2dVector p0, p1;
  int i;
  p1 = corners[3];
  for ( i = 0; i < 4; i++ ) 
  {
    p0 = p1;
    p1 = corners[i];
    twice_area += (p0.x-p1.x)*(p0.y+p1.y);
  }
  if ( twice_area < 0.0 )
  {
    p1 = corners[1];
    corners[1] = corners[3];
    corners[3] = p1;
  }
}

int ON_OBSOLETE_V5_DimAngular::GetDimensionArcSegments(
    ON_OBSOLETE_V5_RECT gdi_text_rect,
    int gdi_height_of_I,
    ON_Xform gdi_to_world,
    const ON_DimStyle& dimstyle,
    double dimscale,
    const ON_Viewport* vp,
    double a[6],
    bool& bInside
    ) const
{
  int rc = 0;

  a[0] = 0.0;
  a[1] = 0.0;

  if ( m_angle <= 0.0 || !ON_IsValid(m_angle) )
    return 0;

  a[1] = m_angle;

  if ( m_radius <= 0.0 || !ON_IsValid(m_radius) || m_angle >= 2.0*ON_PI )
    return 0;

  if ( 0 == gdi_height_of_I )
  {
    // Default to height of Ariel 'I' (this code still works if ON_Font::Constants::AnnotationFontCellHeight != 256)
    gdi_height_of_I = (165*ON_Font::Constants::AnnotationFontCellHeight)/256;
  }

  if ( 0.0 == dimscale )
  {
    dimscale = 1.0;
  }

  double t;

  ON_INTERNAL_OBSOLETE::V5_TextDisplayMode textdisplay = ON_INTERNAL_OBSOLETE::V5TextDisplayModeFromV6DimStyle(dimstyle);

  const double text_height_of_I    = dimscale*dimstyle.TextHeight();
  const double textgap             = dimscale*dimstyle.TextGap();
  const double gdi_to_plane_scale  = text_height_of_I/gdi_height_of_I;
  const double textwidth           = fabs(gdi_to_plane_scale*(gdi_text_rect.right - gdi_text_rect.left));
  const double arrowwidth          = fabs(dimscale*dimstyle.ArrowSize());
  const double tailwidth           = 0.5*arrowwidth;
  const double dimextension        = fabs(dimscale*dimstyle.DimExtension());
  const double a0 = 0.0;
  const double a1 = m_angle;

  double sin_angle = 0.5*dimextension/m_radius;
  if ( sin_angle > 1.0 ) sin_angle = 1.0; else if (sin_angle < -1.0) sin_angle = -1.0;
  const double  dimextension_angle = 2.0*asin(sin_angle);

  sin_angle = 0.5*arrowwidth/m_radius;
  if ( sin_angle > 1.0 ) sin_angle = 1.0; else if (sin_angle < -1.0) sin_angle = -1.0;
  const double arrowangle = 2.0*asin(sin_angle);

  sin_angle = 0.5*tailwidth/m_radius;
  if ( sin_angle > 1.0 ) sin_angle = 1.0; else if (sin_angle < -1.0) sin_angle = -1.0;
  const double tailangle = 2.0*asin(sin_angle);

  // June 7, 2010 - Lowell - Added some special handling for very small dimensions 
  double arrow_angle = arrowangle + tailangle;
  if(arrow_angle > ON_PI * 0.5)
    arrow_angle = ON_PI * 0.5;
  if ( m_radius <= arrowwidth + tailwidth || m_radius*(a1-a0) < 2.0*(arrowwidth) + tailwidth )
  {
    // arc is tiny with respect to arrowhead size - arrowheads have to be "outside"
    // 2 arc segments, arrowheads outside
    a[0] = a0;
    a[1] = a0 - arrow_angle;
    a[2] = a1 + arrow_angle;
    a[3] = a1;
    a[4] = a0;
    a[5] = a1;
    if( dimextension_angle != 0.0)
    {
      a[0] += dimextension_angle;
      a[3] -= dimextension_angle;
    }
    bInside = false;
    return 2;
  }
  
  if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine == textdisplay && m_radius <= 0.5*(textwidth + 2.0*textgap))
  {
    // 2 arc segments, arrowheads outside
    a[0] = a0;
    a[1] = a0 - arrow_angle;
    a[2] = a1 + arrow_angle;
    a[3] = a1;
    a[4] = a0;
    a[5] = a1;
    if( dimextension_angle != 0.0)
    {
      a[0] += dimextension_angle;
      a[3] -= dimextension_angle;
    }
    bInside = false;
    return 2;
  }

  sin_angle = 0.5*(textwidth+2.0*textgap)/m_radius;
  if ( sin_angle > 1.0 ) sin_angle = 1.0; else if (sin_angle < -1.0) sin_angle = -1.0;
  const double textangle = (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine == textdisplay && !m_userpositionedtext)
    ? 2.0*asin(sin_angle)
    : 0.0;

  if ( (a1-a0) <= 2.0*(arrow_angle) + textangle )
  {
    // 2 arc segments, arrowheads outside
    a[0] = a0;
    a[1] = a0 - arrow_angle;
    a[2] = a1 + arrow_angle;
    a[3] = a1;
    a[4] = a0;
    a[5] = a1;
    if( dimextension_angle != 0.0)
    {
      a[0] += dimextension_angle;
      a[3] -= dimextension_angle;
    }
    bInside = false;
    return 2;
  }
  
  if ((ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen == textdisplay && vp) || m_userpositionedtext)
  {
    // use projected rectangle to clip dimension arc
    double aa0, aa1, aa, r0, r1, tt[2];
    ON_3dPoint P, R, c[2];
    ON_2dVector corners[4], N;
    ON_Line ray;
    int i,xi, xrc;
    const ON_Circle circle(ON_xy_plane,1.0);

    ON_3dVector vp_zaxis = (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen == textdisplay && vp)
                         ? vp->CameraZ() 
                         : m_plane.zaxis;

    // 30 July 2012 - Lowell - Slightly shrink the text gap value
    // so that text + gap won't intersect the dim line if when text
    // is moved along the dim line. rr110504
    double gdi_gap = fabs(textgap/gdi_to_plane_scale)-12;
    if(gdi_gap < 0.0) gdi_gap = 0.0;

    R.Set(gdi_text_rect.left-gdi_gap,gdi_text_rect.bottom+gdi_gap,0.0);
    ray.from = gdi_to_world*R; ray.to = ray.from + vp_zaxis;
    P = ( ON_Intersect(ray,m_plane,&t) ) ? ray.PointAt(t) : ray.from;
    m_plane.ClosestPointTo(P,&corners[0].x,&corners[0].y);

    R.Set(gdi_text_rect.right+gdi_gap,gdi_text_rect.bottom+gdi_gap,0.0);
    ray.from = gdi_to_world*R; ray.to = ray.from + vp_zaxis;
    P = ( ON_Intersect(ray,m_plane,&t) ) ? ray.PointAt(t) : ray.from;
    m_plane.ClosestPointTo(P,&corners[1].x,&corners[1].y);

    R.Set(gdi_text_rect.right+gdi_gap,gdi_text_rect.top-gdi_gap,0.0);
    ray.from = gdi_to_world*R; ray.to = ray.from + vp_zaxis;
    P = ( ON_Intersect(ray,m_plane,&t) ) ? ray.PointAt(t) : ray.from;
    m_plane.ClosestPointTo(P,&corners[2].x,&corners[2].y);

    R.Set(gdi_text_rect.left-gdi_gap,gdi_text_rect.top-gdi_gap,0.0);
    ray.from = gdi_to_world*R; ray.to = ray.from + vp_zaxis;
    P = ( ON_Intersect(ray,m_plane,&t) ) ? ray.PointAt(t) : ray.from;
    m_plane.ClosestPointTo(P,&corners[3].x,&corners[3].y);

    // orient projected rect so it is counter-clockwise
    OrientRectHelper(corners);

    aa0 = a0;
    aa1 = a1;
    P.Set(cos(a0)*m_radius,sin(a0)*m_radius,0.0);
    R.Set(cos(a1)*m_radius,sin(a1)*m_radius,0.0);
    for ( i = 0; i < 4; i++ )
    {
      N.x = (corners[i].y-corners[(i+1)%4].y);
      N.y = (corners[(i+1)%4].x-corners[i].x);
      if ( !N.Unitize() )
        continue;
      if ( (P.x - corners[i].x)*N.x + (P.y - corners[i].y)*N.y  < 0.0 )
      {
        // end point not in text box
        aa0 = ON_UNSET_VALUE;
      }
      if ( (R.x - corners[i].x)*N.x + (R.y - corners[i].y)*N.y  < 0.0 )
      {
        // start point not in text box
        aa1 = ON_UNSET_VALUE;
      }
    }

    if ( ON_UNSET_VALUE == aa0 )
      aa0 = aa1;
    else if ( ON_UNSET_VALUE == aa1 )
      aa1 = aa0;

    r1 = corners[3].Length() - m_radius;
    ray.to.x = corners[3].x/m_radius; ray.to.y = corners[3].y/m_radius; 
    ray.to.z = ray.from.z = 0.0;
    for ( i = 0; i < 4; i++ )
    {
      r0 = r1;
      r1 = corners[i].Length() - m_radius;
      ray.from = ray.to;
      ray.to.x = corners[i].x/m_radius; ray.to.y = corners[i].y/m_radius;
      if ( r0 < 0.0 && r1 < 0.0 )
      {
        continue; // ray is inside circle
      }
      if ( r0 > 0.0 && r1 > 0.0 )
      {
        if ( !ray.ClosestPointTo(ON_3dPoint::Origin,&t ) )
          continue;
        R = ray.PointAt(t);
        if ( R.x*R.x + R.y*R.y >= 1.0 )
          continue; // ray is outside circle
      }


      xrc = 0;
      if ( 0.0 == r0 )
        tt[xrc++] = 0.0;

      if ( 0.0 == r1 )
        tt[xrc++] = 1.0;

      if ( 0 == xrc )
        xrc = ON_Intersect(ray,circle,&tt[0],c[0],&tt[1],c[1]);

      if ( xrc < 1 || xrc > 2 )
        continue; // ray does not intersect circle;

      for ( xi = 0; xi < xrc; xi++ )
      {
        if ( tt[xi] < 0.0 || tt[xi] > 1.0 )
          continue; // intersection point not on segment

        P = ray.PointAt(tt[xi]);
        if ( 0.0 == P.x && 0.0 == P.y )
          continue; // bogus

        aa = atan2(P.y,P.x);
        if ( aa < a0 ) aa += 2.0*ON_PI; else if ( aa > a1 ) aa -= 2.0*ON_PI;
        if ( aa < a0 || aa > a1 )
        {
          continue;
        }
        if ( ON_UNSET_VALUE == aa0 )
          aa0 = aa1 = aa;
        else if ( aa < aa0 )
          aa0 = aa;
        else if ( aa > aa1 )
          aa1 = aa;
      }
    }
    if ( ON_UNSET_VALUE != aa0 && ON_UNSET_VALUE != aa1 
        && a0 <= aa0 && aa0 < aa1 && aa1 <= a1 )
    {
      t = arrow_angle;
      if ( aa0 < a0+t && aa1 > a1-t )
      {
        // text box hits both arrowheads
        // 2 arc segments, arrowheads outside
        a[0] = a0;
        a[1] = a0 - arrow_angle;
        a[2] = a1 + arrow_angle;
        a[3] = a1;
        a[4] = a0;
        a[5] = a1;
        if( dimextension_angle != 0.0)
        {
          a[0] += dimextension_angle;
          a[3] -= dimextension_angle;
        }
        bInside = false;
        rc = 2;
      }
      else
      {
        if ( aa0 < a0+t ) aa0 = a0+t;
        if ( aa1 > a1-t ) aa1 = a1-t;
        if ( a0 < aa0 && aa0 < aa1 && aa1 < a1 )
        {
          // clip arc to text rectangle
          // 2 arc segments, arrowheads inside
          a[0] = a0;
          a[1] = aa0;
          a[2] = aa1;
          a[3] = a1;
          a[4] = a0;
          a[5] = a1;
          if( dimextension_angle != 0.0)
          {
            a[0] -= dimextension_angle;
            a[3] += dimextension_angle;
          }
          bInside = true;
          rc = 2;
        }
        else
        {
          // nasty case - don't bother clipping
          // 1 segment, arrows inside
          a[0] = a0;
          a[1] = a1;
          a[2] = a0;
          a[3] = a1;
          a[4] = a0;
          a[5] = a1;
          if( dimextension_angle != 0.0)
          {
            a[0] -= dimextension_angle;
            a[1] += dimextension_angle;
          }
          bInside = true;
          rc = 1;
        }
      }
    }
    else
    {
      // 1 segment, arrows inside
      a[0] = a0;
      a[1] = a1;
      a[2] = a0;
      a[3] = a1;
      a[4] = a0;
      a[5] = a1;
      if( dimextension_angle != 0.0)
      {
        a[0] -= dimextension_angle;
        a[1] += dimextension_angle;
      }
      bInside = true;
      rc = 1;
    }
  }
  else if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine == textdisplay || m_userpositionedtext)
  {
    // 1 segment, arrows inside
    a[0] = a0;
    a[1] = a1;
    a[2] = a0;
    a[3] = a1;
    a[4] = a0;
    a[5] = a1;
    if( dimextension_angle != 0.0)
    {
      a[0] -= dimextension_angle;
      a[1] += dimextension_angle;
    }
    bInside = true;
    rc = 1;
  }
  else if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine == textdisplay)
  {
    // 2 segments, arrows inside
    t = 0.5*((a1-a0) - textangle);
    a[0] = a0;
    a[1] = a0+t;
    a[2] = a1-t;
    a[3] = a1;
    a[4] = a0;
    a[5] = a1;
    if( dimextension_angle != 0.0)
    {
      a[0] -= dimextension_angle;
      a[3] += dimextension_angle;
    }
    bInside = true;
    rc = 2;
  }

  return rc;
}

double ON_OBSOLETE_V5_DimAngular::DimpointOffset(int index) const
{
  const ON_AngularDimension2Extra* pDE = ON_AngularDimension2Extra::AngularDimensionExtra(this);
  if(pDE != 0)
    return pDE->DimpointOffset(index);
  return -1.0;
}
void ON_OBSOLETE_V5_DimAngular::SetDimpointOffset(int index, double offset)
{
  ON_AngularDimension2Extra* pDE = ON_AngularDimension2Extra::AngularDimensionExtra(this);
  if(pDE != 0)
    pDE->SetDimpointOffset(index, offset);
}


//----- ON_OBSOLETE_V5_DimOrdinate -----------------------------------------
ON_OBSOLETE_V5_DimOrdinate::ON_OBSOLETE_V5_DimOrdinate()
{
  m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate;
  SetTextValue(DefaultText());
  SetTextFormula(0);
  m_direction = -1;  // undetermined direction
  m_points.Reserve(ON_OBSOLETE_V5_DimOrdinate::dim_pt_count);
  m_points.SetCount(ON_OBSOLETE_V5_DimOrdinate::dim_pt_count);
  m_points.Zero();
  m_kink_offset_0 = ON_UNSET_VALUE;
  m_kink_offset_1 = ON_UNSET_VALUE;
}

ON_OBSOLETE_V5_DimOrdinate::~ON_OBSOLETE_V5_DimOrdinate()
{
}

bool ON_OBSOLETE_V5_DimOrdinate::Transform( const ON_Xform& xform )
{
  bool rc = xform.IsIdentity();
  if ( !rc)
  {
    return ON_OBSOLETE_V5_Annotation::Transform(xform);
  }
  return rc;
}

ON_2dPoint ON_OBSOLETE_V5_DimOrdinate::Dim2dPoint( int point_index, double default_offset) const
{
  ON_2dPoint p2( ON_UNSET_VALUE, ON_UNSET_VALUE);
  int dir = m_direction;
  if( dir == -1 && ( point_index == offset_pt_0 || point_index == offset_pt_1))
  {
    if( fabs( m_points[definition_pt_index].y - m_points[leader_end_pt_index].y) > 
        fabs( m_points[definition_pt_index].x - m_points[leader_end_pt_index].x))
      dir = 0;
    else
      dir = 1;
  }

  if( point_index >= 0 && point_index < dim_pt_count && m_points.Count() == dim_pt_count)
  {
    p2 = m_points[point_index];
  }
  else if( point_index == text_pivot_pt)
  {
    // ON_3dPoint::UnsetPoint
  }
  else if( point_index == offset_pt_0)
  {
    double offset;
    if( m_kink_offset_0 == ON_UNSET_VALUE)
      offset = default_offset;
    else
      offset = m_kink_offset_0;

    if( dir == x)
    {
      p2 = m_points[leader_end_pt_index];
      if( p2.y > m_points[definition_pt_index].y)
        p2.y -= offset;
      else
        p2.y += offset;
    }
    else if( dir == y)
    {
      p2 = m_points[leader_end_pt_index];
      if( p2.x > m_points[definition_pt_index].x)
        p2.x -= offset;
      else
        p2.x += offset;
    }
  }
  else if( point_index == offset_pt_1)
  {
    double offset0;
    if( m_kink_offset_0 == ON_UNSET_VALUE)
      offset0 = default_offset;
    else
      offset0 = m_kink_offset_0;

    double offset1;
    if( m_kink_offset_1 == ON_UNSET_VALUE)
      offset1 = default_offset;
    else
      offset1 = m_kink_offset_1;

    if( dir == x)
    {
      p2.x = m_points[definition_pt_index].x;
      if( m_points[leader_end_pt_index].y > m_points[definition_pt_index].y)
        p2.y = m_points[leader_end_pt_index].y - offset0 - offset1;
      else
        p2.y = m_points[leader_end_pt_index].y + offset0 + offset1;
    }
    else if( dir == y)
    {
      p2.y = m_points[definition_pt_index].y;
      if( m_points[leader_end_pt_index].x > m_points[definition_pt_index].x)
        p2.x = m_points[leader_end_pt_index].x - offset0 - offset1;
      else
        p2.x = m_points[leader_end_pt_index].x + offset0 + offset1;
    }
  }
  return p2;
}

ON_3dPoint ON_OBSOLETE_V5_DimOrdinate::Dim3dPoint( int point_index, double default_offset) const
{
  ON_2dPoint p2 = Dim2dPoint(point_index, default_offset);
  return (ON_UNSET_VALUE == p2.x) ? ON_3dPoint::UnsetPoint : m_plane.PointAt(p2.x,p2.y);
}

bool ON_OBSOLETE_V5_DimOrdinate::IsValid( ON_TextLog* text_log) const
{
  if ( m_type != ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate)
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimOrdinate - m_type !=  ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate.\n");
    }
    return false;
  }

  if ( !ON_OBSOLETE_V5_Annotation::IsValid( text_log ))
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimOrdinate - invalid ON_OBSOLETE_V5_Annotation base class.\n");
    }
    return false;
  }

  if ( m_points.Count() != 2 )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_DimOrdinate - m_points.Count() = %d (should be 2).\n",m_points.Count());
    }
    return false;
  }

  return true;

}

bool ON_OBSOLETE_V5_DimOrdinate::Write( ON_BinaryArchive& file ) const
{
  // put the entire ON_OBSOLETE_V5_DimOrdinate in a chunk so we can
  // add fields without breaking the file IO for old product.
  bool rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,1);
  if (rc)
  {
    rc = file.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
    if (rc)
    {
      // As of 18 October 2007, the following comment is out of date.
      // But, we still need to write this "extra" chunk so we don't
      // break V4 file writing.
      //
      //   The output of ON_OBSOLETE_V5_Annotation::Write must be wrapped
      //   in an additional chunk because it does not put 
      //   itself in a chunk.  If you don't put it in a chunk,
      //   the versioning in the ON_OBSOLETE_V5_Annotation::Write is useless and
      //   will cause serious IO bugs if fields are ever added.
      rc = ON_OBSOLETE_V5_Annotation::Write( file) ? true : false;
      if (!file.EndWrite3dmChunk() )
        rc = false;
    }
    if (rc)
      rc = file.WriteInt( m_direction);
    // kink offsets, ver 1.1 added 2-4-06
    if (rc)
      rc = file.WriteDouble( m_kink_offset_0);
    if (rc)
      rc = file.WriteDouble( m_kink_offset_1);

    // end of ON_OBSOLETE_V5_DimOrdinate chunk
    if (!file.EndWrite3dmChunk() )
      rc = false;
  }

  return rc;
}

bool ON_OBSOLETE_V5_DimOrdinate::Read( ON_BinaryArchive& file )
{
  int major_version=0, minor_version=0;
  bool rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
  if (rc)
  {
    if ( 1 != major_version )
    {
      rc = false;
    }
    else
    {
      int submajor_version=0, subminor_version=0;

      // subchunk wraps ON_OBSOLETE_V5_Annotation field so this
      // function won't break if ON_OBSOLETE_V5_Annotation changes.
      rc = file.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&submajor_version,&subminor_version);
      if (rc)
      {
        if ( 1 != submajor_version )
          rc = false;
        else
        {
          rc = ON_OBSOLETE_V5_Annotation::Read( file) ? true : false;
        }
        if ( !file.EndRead3dmChunk() )
          rc = false;
      }

      if( rc) 
        rc = file.ReadInt( &m_direction);

      if( minor_version > 0)
      {
        if( rc) 
          rc = file.ReadDouble( &m_kink_offset_0);
        if( rc) 
          rc = file.ReadDouble( &m_kink_offset_1);
      }
    }

    if (!file.EndRead3dmChunk())
      rc = false;
  }
  return rc;
}

double ON_OBSOLETE_V5_DimOrdinate::NumericValue() const
{
  if( m_direction == 0)
    return m_points[1].x - m_points[0].x;
  else
    return m_points[1].y - m_points[0].y;
}

int ON_OBSOLETE_V5_DimOrdinate::StyleIndex() const
{
  return ON_OBSOLETE_V5_Annotation::V5_3dmArchiveDimStyleIndex();
}

void ON_OBSOLETE_V5_DimOrdinate::SetStyleIndex( int i)
{
  ON_OBSOLETE_V5_Annotation::SetV5_3dmArchiveDimStyleIndex( i);
}

bool ON_OBSOLETE_V5_DimOrdinate::GetBBox(
  double* boxmin,
  double* boxmax,
  bool bGrowBox
) const
{
  ON_BoundingBox bbox;
  if ( bGrowBox )
  {
    bbox.m_min.x = boxmin[0]; 
    bbox.m_min.y = boxmin[1]; 
    bbox.m_min.z = boxmin[2];
    bbox.m_max.x = boxmax[0]; 
    bbox.m_max.y = boxmax[1]; 
    bbox.m_max.z = boxmax[2];
    if ( !bbox.IsValid() )
    {
      bbox.Destroy();
      bGrowBox = false;
    }
  }

  if( m_points.Count() == 2)
  {
    ON_3dPointArray P( 2);

    P.Append( m_plane.PointAt( m_points[0].x, m_points[0].y));
    P.Append( m_plane.PointAt( m_points[1].x, m_points[1].y));
    bGrowBox = P.GetBBox(&bbox.m_min.x, &bbox.m_max.x, bGrowBox);
  }

  if ( bGrowBox )
  {
    boxmin[0] = bbox.m_min.x; 
    boxmin[1] = bbox.m_min.y; 
    boxmin[2] = bbox.m_min.z; 
    boxmax[0] = bbox.m_max.x; 
    boxmax[1] = bbox.m_max.y; 
    boxmax[2] = bbox.m_max.z; 
  }

  return bGrowBox;
}

bool ON_OBSOLETE_V5_DimOrdinate::GetTightBoundingBox( ON_BoundingBox& tight_bbox,
                                                 bool bGrowBox,
                                                 const ON_Xform* xform) const
{
  if( m_points.Count() == 2)
  {
    ON_3dPointArray P(2);

    P.Append( m_plane.PointAt( m_points[0].x, m_points[0].y));
    P.Append( m_plane.PointAt( m_points[1].x, m_points[1].y));

    if ( P.GetTightBoundingBox( tight_bbox, bGrowBox, xform))
      bGrowBox = true;
  }
  else if( bGrowBox && !tight_bbox.IsValid())
  {
    tight_bbox.Destroy();
    bGrowBox = false;
  }

  return( 0 != bGrowBox);
}

int ON_OBSOLETE_V5_DimOrdinate::ImpliedDirection() const
{
  int direction = -1;
  const ON_2dPoint& p0 = m_points[definition_pt_index];
  const ON_2dPoint& p1 = m_points[leader_end_pt_index];
  if( fabs( p1.x - p0.x) <= fabs( p1.y - p0.y))
    direction = 0; // measures along x axis
  else
    direction = 1; // measures along y axis
  
  return direction;
} 

int ON_OBSOLETE_V5_DimOrdinate::Direction() const
{
  return m_direction;
} 

void ON_OBSOLETE_V5_DimOrdinate::SetDirection( int direction)
{
  m_direction = direction;
}

const wchar_t* ON_OBSOLETE_V5_DimOrdinate::DefaultText() { return L"<>"; }

double ON_OBSOLETE_V5_DimOrdinate::KinkOffset( int index) const
{
  if( index == 0)
    return m_kink_offset_0;
  else if( index == 1)
    return m_kink_offset_1;
  else
    return ON_UNSET_VALUE;
}

void ON_OBSOLETE_V5_DimOrdinate::SetKinkOffset( int index, double offset)
{
  if( index == 0)
    m_kink_offset_0 = offset;
  else  if( index == 1)
    m_kink_offset_1 = offset;
}

void ON_OBSOLETE_V5_DimOrdinate::CalcKinkPoints( ON_2dPoint p0, ON_2dPoint p1, 
                                            int direction, double default_offset,
                                            ON_2dPoint& k0, ON_2dPoint& k1) const
{
  double offset0 = KinkOffset( 0);
  double offset1 = KinkOffset( 1);

  // if these haven't been set by dragging the offset points
  // use 2*textheight
  if( offset0 == ON_UNSET_VALUE)
    offset0 = default_offset;
  if( offset1 == ON_UNSET_VALUE)
    offset1 = default_offset;

  if( p0[1-direction] > p1[1-direction])
  {
    offset0 = -offset0;
    offset1 = -offset1;
  }

  //double d = fabs( p0[1-direction] - p1[1-direction]);

  if( direction == 0)
  {
    //if( d - fabs( offset0) > default_offset)
    //{
      k1.x = p0.x;
      k1.y = p1.y - offset0 - offset1;
    //}
    //else
    //{
    //  k1.x = p0.x;
    //  k1.y = p1.y + offset0 - offset1;
    //}

    k0.x = p1.x;
    k0.y = p1.y - offset0;
  }
  else
  {
    //if( d - fabs( offset0) > default_offset)
    //{
      k1.x = p1.x - offset0 - offset1;
      k1.y = p0.y;
    //}
    //else
    //{
    //  k1.x = p1.x + offset0 - offset1;
    //  k1.y = p0.y;
    //}

    k0.x = p1.x - offset0;
    k0.y = p1.y;
  }
}



//----- ON_OBSOLETE_V5_TextObject -----------------------------------------------
ON_OBSOLETE_V5_TextObject::ON_OBSOLETE_V5_TextObject()
{
  m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock;
  m_textdisplaymode = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kNormal;
}

ON_OBSOLETE_V5_TextObject::~ON_OBSOLETE_V5_TextObject()
{
}

bool ON_OBSOLETE_V5_TextObject::IsValid( ON_TextLog* text_log ) const
{
  if ( m_type != ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_TextObject - m_type !=  ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock\n");
    }
    return false;
  }

  // 05 March 2009 S. Baer
  // Text blocks with no "printable" characters are considered invalid. Any
  // character with a value greater than 32 (the value of space) is "printable."
  int count = m_usertext.Length();
  bool bValidText = false;
  for( int i=0; i<count; i++ )
  {
    wchar_t c = m_usertext[i];
    // all characters <= space are nonprintable
    if( c > L' ' )
    {
      bValidText = true;
      break;
    }
  }
  // 9 Oct 2010 S. Baer
  // With the addition of text formulas, the user text can be 0 length
  if( !bValidText && count<1 )
  {
    const wchar_t* formula = TextFormula();
    if( formula && formula[0] )
      bValidText = true;
  }

  if( !bValidText )
  {
    if( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_TextObject - m_usertext does not contain printable characters.\n");
    }
    return false;
  }


  if ( !ON_OBSOLETE_V5_Annotation::IsValid( text_log ))
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_TextObject - invalid ON_OBSOLETE_V5_Annotation base class.\n");
    }
    return false;
  }

  if ( 0 != m_points.Count() )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_TextObject - m_points.Count() = %d (should be 0)\n", m_points.Count() );
    }
    return false;
  }

  return true;
}


bool ON_OBSOLETE_V5_TextObject::Write(ON_BinaryArchive& archive) const
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_TextObject
  //    V4 did not have a ON_OBSOLETE_V5_TextObject::Write and simply called
  //    ON_OBSOLETE_V5_Annotation::Write.
  bool rc = false;
  bool bInChunk = (archive.Archive3dmVersion() >= 5);
  if ( bInChunk )
  {
    rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Write(archive)?true:false;
    if (!rc) break;
    if ( !bInChunk )
      break;

    // To write new fields, increment minor version number
    // and write values here.  Ask Dale Lear for help.

    break;
  }

  if ( bInChunk )
  {
    if (!archive.EndWrite3dmChunk())
      rc = false;
  }
  return rc;
}

bool ON_OBSOLETE_V5_TextObject::Read(ON_BinaryArchive& archive)
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_TextObject
  int major_version = 0;
  int minor_version = 0;
  bool rc = false;
  bool bInChunk = (archive.Archive3dmVersion() >= 5 && archive.ArchiveOpenNURBSVersion() >= 200710180);
  if ( bInChunk )
  {
    rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Read(archive)?true:false;
    if (!rc) break;
    if ( !bInChunk || minor_version <= 0 )
      break;

    // read future addition here

    break;
  }

  if ( bInChunk )
  {
    // To read new ON_OBSOLETE_V5_TextObject specific additions,
    // examine the minor version number and read the information
    // here.  Please ask Dale Lear for help.

    if ( !archive.EndRead3dmChunk() )
      rc = false;
  }
  return rc;
}


bool ON_OBSOLETE_V5_TextObject::GetBBox(
        double* boxmin,
        double* boxmax,
        bool bGrowBox
        ) const
{
  ON_BoundingBox bbox;
  if ( bGrowBox )
  {
    bbox.m_min.x = boxmin[0]; 
    bbox.m_min.y = boxmin[1]; 
    bbox.m_min.z = boxmin[2];
    bbox.m_max.x = boxmax[0]; 
    bbox.m_max.y = boxmax[1]; 
    bbox.m_max.z = boxmax[2];
    if ( !bbox.IsValid() )
    {
      bbox.Destroy();
      bGrowBox = false;
    }
  }

  if ( 1 == m_points.Count() )
  {
    ON_2dPoint uv = m_points[0];
    bbox.Set( m_plane.PointAt(uv.x,uv.y), bGrowBox );
    bGrowBox = true;
  }
  else if ( 0 == m_points.Count() )
  {
    bbox.Set( m_plane.origin, bGrowBox );
    bGrowBox = true;
  }

  if ( bGrowBox )
  {
    boxmin[0] = bbox.m_min.x; 
    boxmin[1] = bbox.m_min.y; 
    boxmin[2] = bbox.m_min.z; 
    boxmax[0] = bbox.m_max.x; 
    boxmax[1] = bbox.m_max.y; 
    boxmax[2] = bbox.m_max.z; 
  }

  return bGrowBox;
}





bool ON_OBSOLETE_V5_TextObject::GetTightBoundingBox( 
		ON_BoundingBox& tight_bbox, 
    bool bGrowBox,
		const ON_Xform* xform
    ) const
{
  if ( 1 == m_points.Count() )
  {
    ON_3dPointArray P(1);
    P.Append( m_plane.PointAt(m_points[0].x,m_points[0].y) );
    if ( P.GetTightBoundingBox( tight_bbox, bGrowBox, xform ) )
      bGrowBox = true;
  }
  else if ( bGrowBox && !tight_bbox.IsValid() )
  {
    tight_bbox.Destroy();
    bGrowBox = false;
  }

  return (0!=bGrowBox);
}

bool ON_OBSOLETE_V5_TextObject::Transform( const ON_Xform& xform )
{
  // Dale Lear - this override fixes RR 11114 by correctly
  //             handling non uniform scaling.
  bool rc = xform.IsIdentity();
  if ( !rc)
  {
    ON_Plane xformed_plane = m_plane;
    rc = xformed_plane.Transform(xform);
    if (rc)
    rc = ON_Geometry::Transform(xform)?true:false;
    if (rc)
    {
      ON_3dPoint P0 = xform*m_plane.origin;
      ON_3dPoint P1 = xform*(m_plane.origin + m_plane.xaxis);
      double s = P0.DistanceTo(P1);
      if ( s <= ON_ZERO_TOLERANCE )
      {
        P1 = xform*(m_plane.origin + m_plane.yaxis);
        s = P0.DistanceTo(P1);
      }
      m_plane = xformed_plane;
      if ( s > ON_ZERO_TOLERANCE && fabs(s-1.0) > ON_SQRT_EPSILON )
      {
        s *= m_textheight;
        if ( s > ON_SQRT_EPSILON )
          m_textheight = s;
      }
    }
  }

  return rc;
}

void ON_OBSOLETE_V5_TextObject::SetJustification( unsigned int justification)
{
  m_justification = justification;
}

unsigned int ON_OBSOLETE_V5_TextObject::Justification() const
{
  return m_justification;
}

bool ON_OBSOLETE_V5_TextObject::DrawTextMask() const
{
  const ON_OBSOLETE_V5_TextExtra* pTE = ON_OBSOLETE_V5_TextExtra::TextExtension(this, false);
  if(pTE)
    return pTE->DrawTextMask();
  else
    return false;
}

void ON_OBSOLETE_V5_TextObject::SetDrawTextMask(bool bDraw)
{
  ON_OBSOLETE_V5_TextExtra* pTE = ON_OBSOLETE_V5_TextExtra::TextExtension(this, true);
  if(pTE)
    pTE->SetDrawTextMask(bDraw);
}

int ON_OBSOLETE_V5_TextObject::MaskColorSource() const
{
  const ON_OBSOLETE_V5_TextExtra* pTE = ON_OBSOLETE_V5_TextExtra::TextExtension(this, false);
  if(pTE)
    return pTE->MaskColorSource();
  else
    return 0;
}

void ON_OBSOLETE_V5_TextObject::SetMaskColorSource(int source)
{
  ON_OBSOLETE_V5_TextExtra* pTE = ON_OBSOLETE_V5_TextExtra::TextExtension(this, true);
  if(pTE)
    pTE->SetMaskColorSource(source);
}

ON_Color ON_OBSOLETE_V5_TextObject::MaskColor() const
{
  const ON_OBSOLETE_V5_TextExtra* pTE = ON_OBSOLETE_V5_TextExtra::TextExtension(this, false);
  if(pTE)
    return pTE->MaskColor();
  else
    return 0;
}

void ON_OBSOLETE_V5_TextObject::SetMaskColor(ON_Color color)
{
  ON_OBSOLETE_V5_TextExtra* pTE = ON_OBSOLETE_V5_TextExtra::TextExtension(this, true);
  if(pTE)
    pTE->SetMaskColor(color);
}

double ON_OBSOLETE_V5_TextObject::MaskOffsetFactor() const
{
  const ON_OBSOLETE_V5_TextExtra* pTE = ON_OBSOLETE_V5_TextExtra::TextExtension(this, false);
  if(pTE)
    return pTE->MaskOffsetFactor();
  else
    return 0;
}

void ON_OBSOLETE_V5_TextObject::SetMaskOffsetFactor(double offset)
{
  ON_OBSOLETE_V5_TextExtra* pTE = ON_OBSOLETE_V5_TextExtra::TextExtension(this, true);
  if(pTE)
    pTE->SetMaskOffsetFactor(offset);
}

bool ON_OBSOLETE_V5_TextObject::AnnotativeScaling() const
{
  return m_annotative_scale;
}

void ON_OBSOLETE_V5_TextObject::SetAnnotativeScaling(bool b)
{
  m_annotative_scale = b;
}



//----- ON_OBSOLETE_V5_Leader ------------------------------------------
ON_OBSOLETE_V5_Leader::ON_OBSOLETE_V5_Leader()
{
  m_type = ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader;
  m_textdisplaymode = ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kInLine;
}

ON_OBSOLETE_V5_Leader::~ON_OBSOLETE_V5_Leader()
{
}

bool ON_OBSOLETE_V5_Leader::IsValid( ON_TextLog* text_log ) const
{
  if ( m_type != ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_Leader - m_type !=  ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader\n");
    }
    return false;
  }

  if ( !ON_OBSOLETE_V5_Annotation::IsValid( text_log ))
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_Leader - invalid ON_OBSOLETE_V5_Annotation base class.\n");
    }
    return false;
  }

  if ( m_points.Count() < 2 )
  {
    if ( text_log )
    {
      text_log->Print("ON_OBSOLETE_V5_Leader - m_points.Count() = %d (should be >= 2)\n", m_points.Count() );
    }
    return false;
  }

  return true;
}

bool ON_OBSOLETE_V5_Leader::Write(ON_BinaryArchive& archive) const
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_Leader
  //    V4 did not have a ON_OBSOLETE_V5_Leader::Write and simply called
  //    ON_OBSOLETE_V5_Leader::Write.
  bool rc = false;
  bool bInChunk = (archive.Archive3dmVersion() >= 5);
  if ( bInChunk )
  {
    rc = archive.BeginWrite3dmChunk(TCODE_ANONYMOUS_CHUNK,1,0);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Write(archive)?true:false;
    if (!rc) break;
    if ( !bInChunk )
      break;

    // To write new fields, increment minor version number
    // and write values here.  Ask Dale Lear for help.

    break;
  }

  if ( bInChunk )
  {
    if (!archive.EndWrite3dmChunk())
      rc = false;
  }
  return rc;
}

bool ON_OBSOLETE_V5_Leader::Read(ON_BinaryArchive& archive)
{
  // 18 October 2007 Dale Lear
  //    I added the chunk wrapping so V5 and future versions can
  //    add IO support for information specific to ON_OBSOLETE_V5_Leader
  int major_version = 0;
  int minor_version = 0;
  bool rc = false;
  bool bInChunk = (archive.Archive3dmVersion() >= 5 && archive.ArchiveOpenNURBSVersion() >= 200710180);
  if ( bInChunk )
  {
    rc = archive.BeginRead3dmChunk(TCODE_ANONYMOUS_CHUNK,&major_version,&minor_version);
    if ( !rc )
      return false;
  }
  else
  {
    rc = true;
  }

  while(rc)
  {
    rc = ON_OBSOLETE_V5_Annotation::Read(archive)?true:false;
    if (!rc) break;
    if ( !bInChunk || minor_version <= 0 )
      break;

    // read future addition here

    break;
  }

  if ( bInChunk )
  {
    if ( !archive.EndRead3dmChunk() )
      rc = false;
  }
  return rc;
}

bool ON_OBSOLETE_V5_Leader::GetBBox(
        double* boxmin,
        double* boxmax,
        bool bGrowBox
        ) const
{
  ON_BoundingBox bbox;
  if ( bGrowBox )
  {
    bbox.m_min.x = boxmin[0]; 
    bbox.m_min.y = boxmin[1]; 
    bbox.m_min.z = boxmin[2];
    bbox.m_max.x = boxmax[0]; 
    bbox.m_max.y = boxmax[1]; 
    bbox.m_max.z = boxmax[2];
    if ( !bbox.IsValid() )
    {
      bbox.Destroy();
      bGrowBox = false;
    }
  }

  const int point_count = m_points.Count();
  if ( point_count > 0 )
  {
    ON_3dPointArray P(point_count);
    int i;
    for ( i = 0; i < point_count; i++ )
    {
      ON_2dPoint uv = m_points[i];
      P.Append( m_plane.PointAt(uv.x,uv.y));
    }
    if ( P.GetBoundingBox(bbox,bGrowBox?true:false) )
      bGrowBox = true;
  }

  if ( bGrowBox )
  {
    boxmin[0] = bbox.m_min.x; 
    boxmin[1] = bbox.m_min.y; 
    boxmin[2] = bbox.m_min.z; 
    boxmax[0] = bbox.m_max.x; 
    boxmax[1] = bbox.m_max.y; 
    boxmax[2] = bbox.m_max.z; 
  }

  return bGrowBox;
}



bool ON_OBSOLETE_V5_Leader::GetTightBoundingBox( 
		ON_BoundingBox& tight_bbox, 
    bool bGrowBox,
		const ON_Xform* xform
    ) const
{
  const int point_count = m_points.Count();
  if ( point_count >= 2 )
  {
    ON_3dPointArray P(point_count);
    int i;
    for ( i = 0; i < point_count; i++ )
    {
      ON_2dPoint uv = m_points[i];
      P.Append( m_plane.PointAt(uv.x,uv.y));
    }
    if ( P.GetTightBoundingBox( tight_bbox, bGrowBox, xform ) )
      bGrowBox = true;
  }
  else if ( bGrowBox && !tight_bbox.IsValid() )
  {
    tight_bbox.Destroy();
    bGrowBox = false;
  }

  return (0!=bGrowBox);
}

ON_2dPoint ON_OBSOLETE_V5_Leader::Dim2dPoint(
      int point_index
      ) const
{
  ON_2dPoint p2;
  int point_count = m_points.Count();
  if ( point_index < 0 || point_count < 1 )
  {
    p2.x = p2.y = ON_UNSET_VALUE;
  }
  else
  {
    switch(point_index)
    {
    case arrow_pt_index:
      p2 = m_points[0];
      break;

    case text_pivot_pt:
    case tail_pt:
      p2 = *m_points.Last();
      break;

    default:
      if ( point_index < point_count )
      {
        p2 = m_points[point_index];
      }
      else
      {
        p2.x = p2.y = ON_UNSET_VALUE;
      }
      break;
    }
  }
  return p2;
}

ON_3dPoint ON_OBSOLETE_V5_Leader::Dim3dPoint(
      int point_index
      ) const
{
  ON_2dPoint p2 = Dim2dPoint(point_index);
  return (ON_UNSET_VALUE == p2.x) ? ON_3dPoint::UnsetPoint : m_plane.PointAt(p2.x,p2.y);
}


void ON_OBSOLETE_V5_Leader::AddPoint( const ON_2dPoint& point )
{
  m_points.Append( point);

}

bool ON_OBSOLETE_V5_Leader::RemovePoint( int idx )
{
  bool rc = true;
  if( idx == -1)  // -1 removes the last point
  {
    m_points.Remove();
  }
  else if( idx >= 0 && idx < m_points.Count())
  {
    m_points.Remove( idx);
  }
  else
  {
    rc = false;
  }

  return rc;
}

// April 22, 2010 Lowell - Added to support right justified text on left pointing leader tails rr64292
bool ON_OBSOLETE_V5_Leader::GetTextDirection( ON_2dVector& text_dir ) const 
{
  bool rc = false;
  const int point_count = m_points.Count();
  if ( point_count < 2 )
  {
    text_dir.Set(-1.0,0.0);
  }
  else
  {
    int i; // 20 June 2011 Fixed textdir for leaders with 2 points. rr86801
    for(i = point_count-1; i >= 1; i--)
    {
      text_dir = m_points[point_count-1] -  m_points[i-1];
      if(text_dir.Unitize())
      {
        rc = true;
        break;
      }
      text_dir.Set(-1.0,0.0);
    }
  }
  return rc;
}

bool ON_OBSOLETE_V5_Leader::GetArrowHeadDirection( ON_2dVector& arrowhead_dir ) const
{
  bool rc = false;
  const int point_count = m_points.Count();
  if ( point_count < 2 )
  {
    arrowhead_dir.Set(-1.0,0.0);
  }
  else
  {
    int i;
    for ( i = 1; i < point_count; i++ )
    {
      arrowhead_dir = m_points[0] -  m_points[i];
      if ( arrowhead_dir.Unitize() )
      {
        rc = true;
        break;
      }
      arrowhead_dir.Set(-1.0,0.0);
    }
  }
  return rc;
}

bool ON_OBSOLETE_V5_Leader::GetArrowHeadTip( ON_2dPoint& arrowhead_tip ) const
{
  bool rc = false;
  switch( m_points.Count())
  {
  case 0:
    arrowhead_tip.Set(0.0,0.0);
    break;
  case 1:
    arrowhead_tip = m_points[0];
    break;
  default:
    arrowhead_tip = m_points[0];
    rc = true;
    break;
  }
  return rc;
}



bool ON_OBSOLETE_V5_DimRadial::GetArrowHeadDirection( ON_2dVector& arrowhead_dir ) const
{
  bool rc = false;
  if ( m_points.Count() < 4 )
  {
    arrowhead_dir.Set(-1.0,0.0);
  }
  else
  {
    arrowhead_dir = m_points[1] - m_points[3];
    if ( 0 == (rc=arrowhead_dir.Unitize()) )
    {
      arrowhead_dir = m_points[1] - m_points[2];
      if ( 0 == (rc=arrowhead_dir.Unitize()) )
      {
        arrowhead_dir = m_points[0] - m_points[1];
        rc = arrowhead_dir.Unitize();
      }
    }
  }
  return rc;
}

bool ON_OBSOLETE_V5_DimRadial::GetArrowHeadTip( ON_2dPoint& arrowhead_tip ) const
{
  bool rc = false;
  if ( m_points.Count() >= 2 )
  {
    arrowhead_tip = m_points[1];
    rc = true;
  }
  else
  {
    arrowhead_tip.Set(0.0,0.0);
    rc = false;
  }
  return rc;
}


// class ON_TextDot
//--------------------------------------------------------------------
ON_TextDot::ON_TextDot()
{}

ON_TextDot* ON_TextDot::CreateFromV2AnnotationTextDot(
  const class ON_OBSOLETE_V2_TextDot& V2_text_dot,
  const class ON_3dmAnnotationContext* annotation_context,
  ON_TextDot* destination
)
{
  ON_wString dot_text = V2_text_dot.m_text;
  dot_text.TrimLeft();
  dot_text.TrimRight();
  ON_TextDot* text_dot
    = (nullptr != destination)
    ? destination
    : new ON_TextDot();
  text_dot->SetPrimaryText(dot_text);
  text_dot->SetCenterPoint(V2_text_dot.point);
  return text_dot;
}

ON_TextDot::ON_TextDot(
  ON_3dPoint center_point,
  const wchar_t* primary_text,
  const wchar_t* secondary_text
  )
  : m_center_point(  center_point.IsValid() ? center_point : ON_3dPoint::UnsetPoint )
  , m_primary_text(primary_text)
  , m_secondary_text(secondary_text)
{
}

ON_TextDot::~ON_TextDot()
{}

void ON_TextDot::EmergencyDestroy()
{
  m_center_point = ON_3dPoint::UnsetPoint;
  m_primary_text.EmergencyDestroy();
  m_secondary_text.EmergencyDestroy();
  m_font_face.EmergencyDestroy();
  m_height_in_points = ON_TextDot::DefaultHeightInPoints;
  m_display_bits = 0;
}

bool ON_TextDot::IsValid( 
            ON_TextLog* text_log
            ) const
{
  // 5/6/03 LW made dots with no text valid.
  if ( !m_center_point.IsValid() )
  {
    if ( 0 != text_log )
    {
      text_log->Print("ON_TextDot::CenterPoint() is not valid\n");
    }
    return false;
  }
  return true;
}

void ON_TextDot::Dump( ON_TextLog& log) const
{
  log.Print(L"Center: ");
  log.Print( m_center_point);
  log.Print(L"\n");
  log.Print(L"Primary text: \"%ls\"\n", static_cast<const wchar_t*>(m_primary_text));
  log.Print(L"Secondary text: \"%ls\"\n", static_cast<const wchar_t*>(m_secondary_text));
  log.Print(L"Height in points: %d\n", m_height_in_points);
  log.Print(L"Font face: \"%ls\"\n", static_cast<const wchar_t*>(m_font_face));

}

bool ON_TextDot::Write( ON_BinaryArchive& file) const
{
  bool rc = false;

  for (;;)
  {
    const int minor_version 
      = file.Archive3dmVersion() >= 60
      ? 1
      : 0;
    if (!file.Write3dmChunkVersion(1, minor_version))
      break;

    if (!file.WritePoint(m_center_point))
      break;
    if (!file.WriteInt(m_height_in_points))
      break;
    if (!file.WriteString(m_primary_text))
      break;
    if (!file.WriteString(m_font_face))
      break;

    // June 21, 2015
    //  Dale Lear cleaned this up so runtime bits and file format are independent.
    //  DO NOT modify this display_bits code for future bool values.
    int display_bits = 0;
    if ( AlwaysOnTop() )
      display_bits |= 1;
    if ( Transparent() )
      display_bits |= 2;
    if ( Bold() )
      display_bits |= 4;
    if (Italic() )
      display_bits |= 8;
    if (!file.WriteInt(display_bits))
      break;
    // DO NOT use display bits for future bool values


    if (minor_version >= 1)
    {
      // version 1.1 fields June 21, 2015
      if (!file.WriteString(m_secondary_text))
        break;
    }

    rc = true;
    break;
  }

  return rc;
}

bool ON_TextDot::Read( ON_BinaryArchive& file)
{
  bool rc = false;

  *this = ON_TextDot::Unset;

  int major_version = 0;
  int minor_version = 0;
  while (file.Read3dmChunkVersion(&major_version, &minor_version))
  {
    if (1 != major_version)
      break;

    ON_3dPoint center_point;
    if (!file.ReadPoint(center_point))
      break;
    SetCenterPoint(center_point);

    int height;
    if (!file.ReadInt(&height))
      break;
    SetHeightInPoints(height);

    ON_wString str;
    if (!file.ReadString( str))
      break;
    SetPrimaryText(str);

    if (!file.ReadString( str))
      break;
    SetFontFace(str);
 
    // June 21, 2015
    //  Dale Lear cleaned this up so runtime bits and file format are independent.
    // DO NOT use display bits for future bool values
    int display_bits = 0;
    if (!file.ReadInt( &display_bits))
      break;
    SetAlwaysOnTop( 0 != (1 & display_bits) );
    SetTransparent( 0 != (2 & display_bits) );
    SetBold( 0 != (4 & display_bits) );
    SetItalic( 0 != (8 & display_bits) );
    // DO NOT use display bits for future bool values

    if (minor_version >= 1)
    {
      // version 1.1 fields June 21, 2015
      if (!file.ReadString(str))
        break;
      SetSecondaryText(str);
    }

    rc = true;
    break;
  }

  return rc;
}

ON::object_type ON_TextDot::ObjectType() const
{
  return ON::text_dot;
}

int ON_TextDot::Dimension() const
{
  return 3;
}

bool ON_TextDot::GetBBox( double* box_min, double* box_max, bool grow_box /*= false*/) const
{
  return ON_GetPointListBoundingBox( 3, 0, 1, 3, &m_center_point.x, box_min, box_max, grow_box?true:false );
}

bool ON_TextDot::Transform( const ON_Xform& xform)
{
  TransformUserData( xform);
  return ON_TransformPointList( 3, 0, 1, 3, &m_center_point.x, xform);
}

bool ON_TextDot::IsDeformable() const
{
  return true;
}

bool ON_TextDot::MakeDeformable()
{
  return true;
}

ON_3dPoint ON_TextDot::CenterPoint() const
{
  return m_center_point;
}

void ON_TextDot::SetCenterPoint( ON_3dPoint center_point )
{
  m_center_point = center_point;
}

int ON_TextDot::HeightInPoints() const
{
  // in "points"
  return m_height_in_points;
}

void ON_TextDot::SetHeightInPoints( 
  int height_in_points 
  )
{
  if( height_in_points >= ON_TextDot::MinimumHeightInPoints )
    m_height_in_points = height_in_points;
}

const wchar_t* ON_TextDot::PrimaryText() const 
{
  return static_cast< const wchar_t* >(m_primary_text);
}

const wchar_t* ON_TextDot::SecondaryText() const 
{
  return static_cast< const wchar_t* >(m_secondary_text);
}

static void SetDotText(
  const wchar_t* dot_text,
  bool bCRtoCRLF,
  ON_wString& dot_string
  )
{
  if (nullptr != dot_text)
  {
    // strip leading white space
    while ( dot_text[0] > 0 && dot_text[0] <= 0x20 )
      dot_text++;
  }

  size_t len = ON_wString::Length(dot_text);
    
  // strip trailing white space
  while (len > 0 && dot_text[len-1] <= 0x20 && dot_text[len-1] > 0)
    len--;

  if( len > 0 )
  {
    wchar_t* buffer = (wchar_t*)onmalloc((2 * len + 1)*sizeof(wchar_t));
    size_t j = 0;
    for (size_t i = 0; i < len; i++)
    {
      if (bCRtoCRLF && '\r' == dot_text[i] && '\n' != dot_text[i+1])
      {
        // change \r to \r\n
        buffer[j++] = '\r';
        buffer[j++] = '\n';
      }
      else
      {
        buffer[j++] = dot_text[i];
      }
    }
    buffer[j] = 0;
    dot_string = buffer;
    onfree(buffer);
  }
  else
  {
    dot_string = ON_wString::EmptyString;
  }
}

void ON_TextDot::SetPrimaryText(const wchar_t* primary_dot_text)
{
  SetDotText(primary_dot_text,true,m_primary_text);
}

void ON_TextDot::SetSecondaryText(const wchar_t* secondary_dot_text)
{
  SetDotText(secondary_dot_text,true,m_secondary_text);
}

const wchar_t* ON_TextDot::FontFace() const
{
  return 
    m_font_face.IsEmpty()
    ? ON_TextDot::DefaultFontFace
    : static_cast< const wchar_t* >(m_font_face);
}

void ON_TextDot::SetFontFace( const wchar_t* font_face )
{
  m_font_face = font_face;
  m_font_face.TrimLeftAndRight();
}

static void SetDisplayBitsFromBool(
  bool b,
  unsigned int bit, 
  unsigned int& display_bits
  )
{
  if (b)
    display_bits |= bit;
  else
    display_bits &= (~bit);
}

static bool DisplayBitsToBool(
  unsigned int display_bits,
  unsigned int bit
  )
{
  return (bit == (display_bits & bit) ? true : false);
}

void ON_TextDot::SetAlwaysOnTop(
  bool bAlwaysOnTop
  )
{
  SetDisplayBitsFromBool(bAlwaysOnTop,1,m_display_bits);
}

bool ON_TextDot::AlwaysOnTop() const
{
  return DisplayBitsToBool(m_display_bits,1);
}

void ON_TextDot::SetTransparent(
  bool bTransparent
  )
{
  SetDisplayBitsFromBool(bTransparent,2,m_display_bits);
}

bool ON_TextDot::Transparent() const
{
  return DisplayBitsToBool(m_display_bits,2);
}

void ON_TextDot::SetBold(
  bool bBold
  )
{
  SetDisplayBitsFromBool(bBold,4,m_display_bits);
}

bool ON_TextDot::Bold() const
{
  return DisplayBitsToBool(m_display_bits,4);
}

void ON_TextDot::SetItalic(bool bItalic)
{
  SetDisplayBitsFromBool(bItalic,8,m_display_bits);
}

bool ON_TextDot::Italic() const
{
  return DisplayBitsToBool(m_display_bits,8);
}

//////// deprecated functions /////////
const ON_3dPoint& ON_TextDot::Point() const
{
  //Perform same functionality as CenterPoint
  return m_center_point;
}
void ON_TextDot::SetPoint(const ON_3dPoint& point)
{
  SetCenterPoint(point);
}
const wchar_t* ON_TextDot::TextString() const
{
  return PrimaryText();
}
void ON_TextDot::SetTextString(const wchar_t* string)
{
  SetPrimaryText(string);
}
////////////////////////////////////////


ON_OBSOLETE_V5_AnnotationText::ON_OBSOLETE_V5_AnnotationText()
{
  memset(&m_rect,0,sizeof(m_rect));
}

ON_OBSOLETE_V5_AnnotationText::~ON_OBSOLETE_V5_AnnotationText()
{
}

ON_OBSOLETE_V5_AnnotationText& ON_OBSOLETE_V5_AnnotationText::operator=(const char* s)
{
  SetText(s);
  return *this;
}

ON_OBSOLETE_V5_AnnotationText& ON_OBSOLETE_V5_AnnotationText::operator=(const wchar_t* s)
{
  SetText(s);
  return *this;
}

void ON_OBSOLETE_V5_AnnotationText::SetText(const char* s)
{
  ON_wString::operator=(s);
  memset(&m_rect,0,sizeof(m_rect));
}

void ON_OBSOLETE_V5_AnnotationText::SetText(const wchar_t* s)
{
  ON_wString::operator=(s);
  memset(&m_rect,0,sizeof(m_rect));
}

bool ON_OBSOLETE_V5_Annotation::GetTextXform( 
      ON_OBSOLETE_V5_RECT gdi_text_rect,
      const ON_Font& font,
      const ON_DimStyle* dimstyle,
      double dimscale,
      const ON_Viewport* vp,
      const ON_Xform* model_xform,
      ON_Xform& xform
      ) const
{
  int gdi_height_of_I = font.FontMetrics().AscentOfI();
  const double textheight = dimstyle ? dimstyle->TextHeight() : m_textheight;
  double textgap =  dimstyle ? dimstyle->TextGap() : 0.0;
  const ON_INTERNAL_OBSOLETE::V5_TextDisplayMode textalignment 
    = dimstyle ? ON_INTERNAL_OBSOLETE::V5TextDisplayModeFromV6DimStyle(*dimstyle) 
    : ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kNormal;
  const ON_3dVector cameraX = (vp) ? vp->CameraX() : m_plane.xaxis;
  const ON_3dVector cameraY = (vp) ? vp->CameraY() : m_plane.yaxis;
  if(dimstyle)
  {
    // - Oct 4, 07 LW Get correct text gap using 
    // multi-line tolerance text since GetTextXform doesn't do that.
    if(
      ( ON_DimStyle::tolerance_format::Deviation == dimstyle->ToleranceFormat() || ON_DimStyle::tolerance_format::Limits == dimstyle->ToleranceFormat() ) 
      &&
      ( Type() == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear || Type() == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned) )
        textgap += textheight * 0.5;
  }
  return GetTextXform( 
      gdi_text_rect,
      gdi_height_of_I,
      textheight, textgap, textalignment,
      dimscale,
      cameraX, cameraY, 
      model_xform,
      xform
      );
}



static bool GetLeaderEndAndDirection( const ON_OBSOLETE_V5_Annotation* pAnn,
                                     ON_2dPoint& E,
                                     ON_2dVector& R )
{
  bool rc = false;

  ON_INTERNAL_OBSOLETE::V5_eAnnotationType ann_type = pAnn->m_type;
  const ON_2dPointArray& ann_m_points = pAnn->m_points;


  R.Set(1.0,0.0); // unit vector points to end
  E.Set(0.0,0.0); // end point

  if ( ann_m_points.Count() >= 4 && (ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter == ann_type || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius == ann_type) )
  {
    E = ann_m_points[2]; // end of radial dimension
    R = E - ann_m_points[3];
    if ( !R.Unitize() )
    {
      R = E - ann_m_points[1];
      if ( !R.Unitize() )
      {
        R = E - ann_m_points[0];
        if ( !R.Unitize() )
        {
          R.Set(1.0,0.0);
        }
      }
    }
    rc = true;
  }
  else if ( ann_m_points.Count() >= 2 && ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader == ann_type )
  {
    int i;
    E = *ann_m_points.Last();
    for (i = ann_m_points.Count()-2; i >= 0; i-- )
    {
      R = E - ann_m_points[i];
      if ( R.Unitize() )
      {
        break;
      }
      R.Set(1.0,0.0);
    }
    rc = true;
  }
  else if ( ann_m_points.Count() >= 2 && ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate == ann_type )
  {
    E = ann_m_points[1];

    int direction = (( ON_OBSOLETE_V5_DimOrdinate*)pAnn)->Direction();
    if( direction == -1)
    {
      if( fabs( ann_m_points[1].x - ann_m_points[0].x) 
       <= fabs( ann_m_points[1].y - ann_m_points[0].y))
        direction = 0;
      else
        direction = 1;
    }

    if( direction == 0)
      R.Set( 0.0, ann_m_points[1].y - ann_m_points[0].y);
    else
      R.Set( ann_m_points[1].x - ann_m_points[0].x, 0.0);

    if( !R.Unitize())
      R.Set(1.0,0.0);

    rc = true;
  }

  return rc;
}

// Oct 30, 07 - LW
// This function should not be used any longer
bool ON_OBSOLETE_V5_Annotation::GetTextXform(
  ON_OBSOLETE_V5_RECT gdi_text_rect,
  int gdi_height_of_I,
  double dimstyle_textheight,
  double dimstyle_textgap,
  ON_INTERNAL_OBSOLETE::V5_TextDisplayMode dimstyle_textalignment,
  double dimscale,
  ON_3dVector cameraX,
  ON_3dVector cameraY,
  ON_Xform& xform
  ) const
{
  ON_ERROR("This function should not be used. Use the version that takes a model transform argument.");
  return false;
}
  //const ON_OBSOLETE_V5_Annotation* ann = this;

  //const ON_INTERNAL_OBSOLETE::V5_eAnnotationType ann_type = ann->m_type;

  //if ( 0 == gdi_height_of_I )
  //{
  //  // Default to height of Ariel 'I'
  //  gdi_height_of_I = (165*ON_Font::Constants::AnnotationFontCellHeight)/256;
  //}

  //if ( 0.0 == dimscale )
  //{
  //  dimscale = 1.0;
  //}

  //dimstyle_textheight *= dimscale;
  //dimstyle_textgap *= dimscale;

  //double textheight = ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock == ann_type )
  //                  ? m_textheight*dimscale
  //                  : dimstyle_textheight;
  //if ( 0.0 == textheight )
  //  textheight = 1.0;

  //ON_3dVector cameraZ = ON_CrossProduct( cameraX, cameraY );
  //if ( fabs( 1.0 - cameraZ.Length() ) > ON_SQRT_EPSILON )
  //{
  //  cameraZ.Unitize();
  //}

  //// This xform is a scale from Windows gdi coordinates 
  //// to annotation plane coordinates.
  //const double gdi_to_plane_scale = textheight/gdi_height_of_I;
  //ON_Xform gdi_to_plane(1.0);
  //gdi_to_plane.m_xform[0][0] =  gdi_to_plane_scale;
  //gdi_to_plane.m_xform[1][1] = -gdi_to_plane_scale;

  //// width and height of text line in Rhino units.
  //const double text_line_width  = gdi_to_plane_scale*(gdi_text_rect.right - gdi_text_rect.left);
  ////const double text_line_height = gdi_to_plane_scale*(gdi_text_rect.bottom - gdi_text_rect.top);

  //if ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock == ann_type )
  //{
  //  // The orientation of the text is text blocks
  //  // does not depend on the view or text alignment
  //  // settings.  The position and orientation of 
  //  // the text in every other annotation depends on
  //  // the view and text alignment settings.  
  //  //
  //  // It simplifies the code for the rest of the
  //  // annotation settings to quickly deal with text
  //  // blocks here.
  //  ON_Xform plane_to_world(1.0);
  //  plane_to_world.Rotation(ON_xy_plane,ann->m_plane);
  //  xform = plane_to_world*gdi_to_plane;
  //  return true;
  //}


  //// text_position_mode
  ////   1 = linear, aligned, or anglular dimension
  ////       (dimension definition determines center point of text box)
  ////   2 = radial, diameter, leader
  ////       (dimension definition determined end point of text box)
  //int position_style = 0;
  //switch( ann_type )
  //{
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned:
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear:
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular:
  //  // dimension definition determines center point of text box
  //  position_style = 1;
  //  break;

  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader:
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius:
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter:
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate:
  //  // dimension definition determines end of text box
  //  position_style = 2;
  //  break;

  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock:
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing:
  //  break;
  //}


  //// This translation puts the center of the fist line of text at
  //// (0,0) in the annotation's plane.
  //if ( ON::dtHorizontal != dimstyle_textalignment || 1 == position_style )
  //{

  //  gdi_to_plane.m_xform[0][3] = -0.5*text_line_width;
  //  gdi_to_plane.m_xform[0][3] = -0.5*text_line_width;
  //}
  //gdi_to_plane.m_xform[1][3] = -0.5*textheight;

  //if ( ON::dtHorizontal != dimstyle_textalignment )
  //{
  //  if ( ((cameraZ*m_plane.zaxis) < -ON_SQRT_EPSILON) )
  //  {
  //    // Viewing dimension from the backside
  //    ON_Xform flip(1.0);
  //    switch ( position_style )
  //    {
  //    case 1: // ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear, ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned, ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular
  //      flip.m_xform[0][0] = -1.0;
  //      flip.m_xform[0][3] = gdi_text_rect.left + gdi_text_rect.right;
  //      break;

  //    case 2: // ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter, ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius, ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader
  //      flip.m_xform[1][1] = -1.0;
  //      flip.m_xform[1][3] = gdi_text_rect.top + gdi_text_rect.bottom;
  //      break;
  //    }
  //    gdi_to_plane = gdi_to_plane*flip;
  //  }
  //}

  //// text_centering_rotation rotates about the "center".  Angular,
  //// radial, and leader dimensions use this rotation.
  //ON_2dVector text_centering_rotation(1.0,0.0);

  //// text_centering_translation is a small translation deals with
  //// text that is above or to the right of the "center" point.  
  //// It is no larger than dimstyle_gap + 1/2 the size of the
  //// text's bounding box.
  //ON_2dVector text_centering_translation(0.0,0.0);

  //double x, y;

  //if ( ON::dtHorizontal != dimstyle_textalignment )
  //{
  //  if ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear  == ann_type || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned == ann_type )
  //  {
  //    if ( ON::dtAboveLine == dimstyle_textalignment )
  //    {
  //      text_centering_translation.y =  0.5*textheight+dimstyle_textgap;
  //    }
  //    y =  ann->m_plane.yaxis*cameraY;
  //    x = -ann->m_plane.yaxis*cameraX;
  //    if ( fabs(y) <= ON_SQRT_EPSILON && fabs(x) > ON_SQRT_EPSILON )
  //    {
  //      y = x;
  //    }
  //    if ( y < 0.0 )
  //    {
  //      text_centering_translation.Reverse();
  //      text_centering_rotation.Reverse(); // rotate 180 degrees
  //    }
  //  }
  //  else if ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular == ann_type )
  //  {
  //    // This transform rotates the text in the annotation plane.
  //    const ON_OBSOLETE_V5_DimAngular* angular_dim = ON_OBSOLETE_V5_DimAngular::Cast(ann);
  //    if ( 0 != angular_dim )
  //    {
  //      double a = 0.5*angular_dim->m_angle;
  //      ON_2dVector R(cos(a),sin(a));
  //      a -= 0.5*ON_PI;
  //      text_centering_rotation.x = cos(a);
  //      text_centering_rotation.y = sin(a);
  //      ON_3dVector V = R.x*m_plane.xaxis + R.y*m_plane.yaxis;
  //      x = V*cameraX;
  //      y = V*cameraY;
  //      if ( fabs(y) <= ON_SQRT_EPSILON && fabs(x) > ON_SQRT_EPSILON )
  //      {
  //        y = -x;
  //      }
  //      if ( y < 0.0 )
  //      {
  //        text_centering_rotation.Reverse(); // add another 180 degrees of rotation
  //      }

  //      if ( ON::dtAboveLine == dimstyle_textalignment )
  //      {
  //        y = 0.5*textheight + dimstyle_textgap;
  //        text_centering_translation.x = -y*text_centering_rotation.y;
  //        text_centering_translation.y =  y*text_centering_rotation.x;
  //      }
  //    }
  //  }
  //  else if (    ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter == ann_type 
  //            || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius == ann_type 
  //            || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader == ann_type 
  //            || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate == ann_type)
  //  {
  //    ON_2dPoint E(0.0,0.0); // end point
  //    ON_2dVector R(1.0,0.0); // unit vector from penultimate point to end point
  //    GetLeaderEndAndDirection( this, E, R );

  //    text_centering_rotation = R;

  //    text_centering_translation = (dimstyle_textgap + 0.5*text_line_width)*text_centering_rotation;

  //    ON_3dVector V = text_centering_rotation.x*m_plane.xaxis + text_centering_rotation.y*m_plane.yaxis;
  //    x = V*cameraX;
  //    y = V*cameraY;
  //    if ( fabs(x) <= ON_SQRT_EPSILON && fabs(y) > ON_SQRT_EPSILON )
  //    {
  //      x = y;
  //    }
  //    if ( x < 0.0 )
  //    {
  //      text_centering_rotation.Reverse(); // rotate 180 degrees
  //    }
  //  }
  //}

  //ON_Xform text_centering_xform(1.0);
  //text_centering_xform.m_xform[0][0] =  text_centering_rotation.x;
  //text_centering_xform.m_xform[0][1] = -text_centering_rotation.y;
  //text_centering_xform.m_xform[1][0] =  text_centering_rotation.y;
  //text_centering_xform.m_xform[1][1] =  text_centering_rotation.x;
  //// Since the translation happens after the rotation about (0,0),
  //// we can just tack it on here.
  //text_centering_xform.m_xform[0][3] =  text_centering_translation.x;
  //text_centering_xform.m_xform[1][3] =  text_centering_translation.y;

  //// This transform translates the text in the annotation plane
  //// It can be a large translation
  //ON_2dVector text_offset_translation(0.0,0.0); // CRhinoText::Offset() = text->Offset()
  //switch( ann_type )
  //{
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear:
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned:
  //  if ( m_points.Count() >= ON_OBSOLETE_V5_DimLinear::dim_pt_count )
  //  {
  //    const ON_OBSOLETE_V5_DimLinear* linear_dim = ON_OBSOLETE_V5_DimLinear::Cast(ann);
  //    if ( linear_dim )
  //    {
  //      text_offset_translation = linear_dim->Dim2dPoint(ON_OBSOLETE_V5_DimLinear::text_pivot_pt);
  //    }
  //  }
  //  break;

  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular:
  //  if ( m_points.Count() >= ON_OBSOLETE_V5_DimAngular::dim_pt_count )
  //  {
  //    const ON_OBSOLETE_V5_DimAngular* angular_dim = ON_OBSOLETE_V5_DimAngular::Cast(ann);
  //    if ( angular_dim )
  //    {
  //      text_offset_translation = angular_dim->Dim2dPoint(ON_OBSOLETE_V5_DimAngular::text_pivot_pt);
  //    }
  //  }
  //  break;

  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter:
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius:
  //  if ( m_points.Count() >= ON_OBSOLETE_V5_DimRadial::dim_pt_count )
  //  {
  //    // No user positioned text on radial dimensions.
  //    text_offset_translation = m_points[ON_OBSOLETE_V5_DimRadial::tail_pt_index];
  //  }
  //  break;

  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader:
  //  if ( m_points.Count() > 0 )
  //  {
  //    // No user positioned text on leaders.
  //    text_offset_translation = *m_points.Last();
  //  }
  //  break;

  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate:
  //  if ( m_points.Count() == 2 )
  //  {
  //    // No user positioned text on leaders.
  //    text_offset_translation = m_points[1];
  //  }
  //  break;

  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock:
  //case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing:
  //  break;
  //}

  //ON_Xform plane_translation(1.0);
  //plane_translation.m_xform[0][3] = text_offset_translation.x;
  //plane_translation.m_xform[1][3] = text_offset_translation.y;

  //// this transform maps a point in the annotation plane to world coordinates
  //ON_Xform plane_to_world(1.0);
  //plane_to_world.Rotation(ON_xy_plane,ann->m_plane);

  //ON_Xform horizonal_xform(1.0);
  //if ( ON::dtHorizontal == dimstyle_textalignment )
  //{
  //  ON_3dPoint fixed_point = ann->m_plane.PointAt(text_offset_translation.x,text_offset_translation.y);
  //  horizonal_xform.Rotation( 
  //      fixed_point,
  //      ann->m_plane.xaxis,
  //      ann->m_plane.yaxis,
  //      ann->m_plane.zaxis,
  //      fixed_point,
  //      cameraX,
  //      cameraY,
  //      cameraZ
  //      );

  //  if ( 2 == position_style )
  //  {
  //    // leaders, radial, and diameter
  //    ON_2dPoint E(0.0,0.0); // end point
  //    ON_2dVector R(1.0,0.0); // unit vector from penultimate point to end point
  //    GetLeaderEndAndDirection( this, E, R );
  //    ON_3dVector V = R.x*m_plane.xaxis + R.y*m_plane.yaxis;
  //    x = V*cameraX;
  //    y = ( x > -ON_SQRT_EPSILON )
  //      ? dimstyle_textgap
  //      : -(dimstyle_textgap + text_line_width);
  //    V = y*cameraX;
  //    horizonal_xform.m_xform[0][3] += V.x;
  //    horizonal_xform.m_xform[1][3] += V.y;
  //    horizonal_xform.m_xform[2][3] += V.z;
  //  }
  //}

  //ON_Xform gdi_to_world;
  //gdi_to_world = horizonal_xform
  //              * plane_to_world
  //              * plane_translation
  //              * text_centering_xform
  //              * gdi_to_plane;

  //xform = gdi_to_world;

  //return true;
//}

//static bool do_plane_translation = true;
//static bool do_text_centering_xform = true;
//static bool do_text_centering_rotation = true;
//static bool do_text_centering_translation = true;
//static bool do_mirror_flip = true;
//static bool do_flip_x = true;
//static bool do_flip_y = true;

// New function added Oct 30, 07 - LW 
// To use model xform to draw annotation in blocks correctly
bool ON_OBSOLETE_V5_Annotation::GetTextXform( 
      ON_OBSOLETE_V5_RECT gdi_text_rect,
      int gdi_height_of_I,
      double dimstyle_textheight,
      double dimstyle_textgap,
      ON_INTERNAL_OBSOLETE::V5_TextDisplayMode dimstyle_textalignment,
      double dimscale,
      ON_3dVector cameraX,
      ON_3dVector cameraY,
      const ON_Xform* model_xform,
      ON_Xform& xform
      ) const
{
  ON_Xform mxi;
  if( model_xform)
  {
    mxi = model_xform->Inverse();
    cameraX.Transform( mxi);
    cameraY.Transform( mxi);
  }
  const ON_OBSOLETE_V5_Annotation* ann = this;

  const ON_INTERNAL_OBSOLETE::V5_eAnnotationType ann_type = ann->m_type;

  if ( 0 == gdi_height_of_I )
  {
    // Default to height of Ariel 'I'
    gdi_height_of_I = (165*ON_Font::Constants::AnnotationFontCellHeight)/256;
  }

  if ( 0.0 == dimscale )
  {
    dimscale = 1.0;
  }

  dimstyle_textheight *= dimscale;
  dimstyle_textgap *= dimscale;

  double textheight = ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock == ann_type )
                    ? m_textheight*dimscale
                    : dimstyle_textheight;
  if ( 0.0 == textheight )
    textheight = 1.0;

  ON_3dVector cameraZ = ON_CrossProduct( cameraX, cameraY );
  if ( fabs( 1.0 - cameraZ.Length() ) > ON_SQRT_EPSILON )
  {
    cameraZ.Unitize();
  }

  // This xform is a scale from Windows gdi coordinates 
  // to annotation plane coordinates.
  const double gdi_to_plane_scale = textheight/gdi_height_of_I;
  ON_Xform gdi_to_plane(ON_Xform::IdentityTransformation);
  gdi_to_plane.m_xform[0][0] =  gdi_to_plane_scale;
  gdi_to_plane.m_xform[1][1] = -gdi_to_plane_scale;

  // width and height of text line in Rhino units.
  const double text_line_width  = gdi_to_plane_scale*(gdi_text_rect.right - gdi_text_rect.left);
  //const double text_line_height = gdi_to_plane_scale*(gdi_text_rect.bottom - gdi_text_rect.top);

  if ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock == ann_type )
  {
    // The orientation of the text is text blocks
    // does not depend on the view or text alignment
    // settings.  The position and orientation of 
    // the text in every other annotation depends on
    // the view and text alignment settings.  
    //
    // It simplifies the code for the rest of the
    // annotation settings to quickly deal with text
    // blocks here.
    ON_Xform plane_to_world(ON_Xform::IdentityTransformation);
    plane_to_world.Rotation(ON_xy_plane,ann->m_plane);
    xform = plane_to_world*gdi_to_plane;
    return true;
  }

  // text_position_mode
  //   1 = linear, aligned, or anglular dimension
  //       (dimension definition determines center point of text box)
  //   2 = radial, diameter, leader
  //       (dimension definition determined end point of text box)
  int position_style = 0;
  switch( ann_type )
  {
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular:
    // dimension definition determines center point of text box
    position_style = 1;
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader:
    if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen == dimstyle_textalignment)
      position_style = 1;
    else
      position_style = 2;
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate:
    // dimension definition determines end of text box
    position_style = 2;
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing:
    break;
  }

  // This translation puts the center of the fist line of text at
  // (0,0) in the annotation's plane.
  if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen != dimstyle_textalignment || 1 == position_style)
  {
    if((m_justification & tjRight) == tjRight)
      gdi_to_plane.m_xform[0][3] = 0.5*text_line_width;
    else
      gdi_to_plane.m_xform[0][3] = -0.5*text_line_width;
  }
  gdi_to_plane.m_xform[1][3] = -0.5*textheight;

  if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen != dimstyle_textalignment)
  {
    if ( ((cameraZ*m_plane.zaxis) < -ON_SQRT_EPSILON) )
    {
      // Viewing dimension from the backside
      ON_Xform flip(ON_Xform::IdentityTransformation);
      switch ( position_style )
      {
      case 1: // ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear, ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned, ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular
        flip.m_xform[0][0] = -1.0;
        flip.m_xform[0][3] = gdi_text_rect.left + gdi_text_rect.right;
        break;

      case 2: // ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter, ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius, ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader
            //flip.m_xform[1][1] = -1.0;
            //flip.m_xform[1][3] = -(gdi_text_rect.top + gdi_text_rect.bottom);
        break;
      }
      gdi_to_plane = gdi_to_plane*flip;
    }
  }

  // text_centering_rotation rotates about the "center".  Angular,
  // radial, and leader dimensions use this rotation.
  ON_2dVector text_centering_rotation(1.0,0.0);

  // text_centering_translation is a small translation deals with
  // text that is above or to the right of the "center" point.  
  // It is no larger than dimstyle_gap + 1/2 the size of the
  // text's bounding box.
  ON_2dVector text_centering_translation(0.0,0.0);
  double x = 1.0, y = 1.0;
  ON_Xform xfs(ON_Xform::IdentityTransformation);

  if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen != dimstyle_textalignment)
  {
    if ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear  == ann_type || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned == ann_type )
    {
      if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine == dimstyle_textalignment)
      {
        text_centering_translation.y =  0.5*textheight+dimstyle_textgap;
      }
      y =  ann->m_plane.yaxis*cameraY;
      x = -ann->m_plane.yaxis*cameraX;
      if ( fabs(y) <= ON_SQRT_EPSILON && fabs(x) > ON_SQRT_EPSILON )
      {
        y = x;
      }
      if ( y < 0.0 )
      {
        text_centering_translation = -text_centering_translation;
        text_centering_rotation = -text_centering_rotation; // rotate 180 degrees
      }
    }
    else if ( ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular == ann_type )
    {
      // This transform rotates the text in the annotation plane.
      const ON_OBSOLETE_V5_DimAngular* angular_dim = ON_OBSOLETE_V5_DimAngular::Cast(ann);
      if ( 0 != angular_dim )
      {
        double a = 0.5*angular_dim->m_angle;
        ON_2dVector R(cos(a),sin(a));
        a -= 0.5*ON_PI;
        text_centering_rotation.x = cos(a);
        text_centering_rotation.y = sin(a);
        ON_3dVector V = R.x*m_plane.xaxis + R.y*m_plane.yaxis;
        x = V*cameraX;
        y = V*cameraY;
        if ( fabs(y) <= ON_SQRT_EPSILON && fabs(x) > ON_SQRT_EPSILON )
        {
          y = -x;
        }
        if ( y < 0.0 )
        {
          text_centering_rotation = -text_centering_rotation; // add another 180 degrees of rotation
        }

        if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kAboveLine == dimstyle_textalignment)
        {
          y = 0.5*textheight + dimstyle_textgap;
          text_centering_translation.x = -y*text_centering_rotation.y;
          text_centering_translation.y =  y*text_centering_rotation.x;
        }
      }
    }
    else if (    ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter == ann_type 
              || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius == ann_type 
              || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader == ann_type 
              || ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate == ann_type)
    {
      // 30 Jan, 2015 - redid this again rh-29493, rh-29540
      ON_2dPoint E(0.0,0.0); // end point
      ON_2dVector R(1.0,0.0); // unit vector from penultimate point to end point
      GetLeaderEndAndDirection( this, E, R );
      text_centering_rotation = R;
      text_centering_translation = (dimstyle_textgap + 0.5*text_line_width)*text_centering_rotation;

      ON_3dPoint p0 = m_plane.origin;
      ON_3dPoint prx = m_plane.PointAt(R.x, R.y);
      ON_3dPoint pry = m_plane.PointAt(-R.y, R.x);

      ON_3dVector xr = prx - p0;  // 3d direction of text x
      ON_3dVector yr = pry - p0;  // 3d direction of text y

      if (xr * cameraX <= ON_ZERO_TOLERANCE)     // 22 April 2015 - Lowell - Fixed rh-30239
        xfs.m_xform[0][0] = -1.0;
      if (yr * cameraY <= ON_ZERO_TOLERANCE)
        xfs.m_xform[1][1] = -1.0;
    }
  }
  else if(ann_type == ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader)
  {
    if((m_justification & tjRight) == tjRight)
      text_centering_translation.Set(-(dimstyle_textgap + 0.5*text_line_width), 0.0);
    else if((m_justification & tjLeft) == tjLeft)
      text_centering_translation.Set(dimstyle_textgap + 0.5*text_line_width, 0.0);
  }

  ON_Xform text_centering_xform(ON_Xform::IdentityTransformation);
  text_centering_xform.m_xform[0][0] =  text_centering_rotation.x;
  text_centering_xform.m_xform[0][1] = -text_centering_rotation.y;
  text_centering_xform.m_xform[1][0] =  text_centering_rotation.y;
  text_centering_xform.m_xform[1][1] =  text_centering_rotation.x; 

  text_centering_xform = text_centering_xform * xfs;

  // Since the translation happens after the rotation about (0,0),
  // we can just tack it on here.
  text_centering_xform.m_xform[0][3] =  text_centering_translation.x;
  text_centering_xform.m_xform[1][3] =  text_centering_translation.y;

  // This transform translates the text in the annotation plane
  // from the plane origin to the final location of the annotation text
  // It can be a large translation
  ON_2dVector text_offset_translation(0.0,0.0); // CRhinoText::Offset() = text->Offset()
  switch( ann_type )
  {
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned:
    if ( m_points.Count() >= ON_OBSOLETE_V5_DimLinear::dim_pt_count )
    {
      const ON_OBSOLETE_V5_DimLinear* linear_dim = ON_OBSOLETE_V5_DimLinear::Cast(ann);
      if ( linear_dim )
      {
        text_offset_translation = linear_dim->Dim2dPoint(ON_OBSOLETE_V5_DimLinear::text_pivot_pt);
      }
    }
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular:
    if ( m_points.Count() >= ON_OBSOLETE_V5_DimAngular::dim_pt_count )
    {
      const ON_OBSOLETE_V5_DimAngular* angular_dim = ON_OBSOLETE_V5_DimAngular::Cast(ann);
      if ( angular_dim )
      {
        text_offset_translation = angular_dim->Dim2dPoint(ON_OBSOLETE_V5_DimAngular::text_pivot_pt);
      }
    }
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius:
    if ( m_points.Count() >= ON_OBSOLETE_V5_DimRadial::dim_pt_count )
    {
      // No user positioned text on radial dimensions.
      text_offset_translation = m_points[ON_OBSOLETE_V5_DimRadial::tail_pt_index];
    }
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader:
    if ( m_points.Count() > 0 )
    {
      // No user positioned text on leaders.
      text_offset_translation = *m_points.Last();
    }
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate:
    if ( m_points.Count() == 2 )
    {
      // No user positioned text on leaders.
      text_offset_translation = m_points[1];
    }
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing:
    break;
  }

  ON_Xform plane_translation(ON_Xform::IdentityTransformation);
  plane_translation.m_xform[0][3] = text_offset_translation.x;
  plane_translation.m_xform[1][3] = text_offset_translation.y;

  // this transform maps a point in the annotation plane to world coordinates
  ON_Xform plane_to_world(ON_Xform::IdentityTransformation);
  plane_to_world.Rotation(ON_xy_plane,ann->m_plane);

  ON_Xform horizonal_xform(ON_Xform::IdentityTransformation);
  if (ON_INTERNAL_OBSOLETE::V5_TextDisplayMode::kHorizontalToScreen == dimstyle_textalignment)
  {
    ON_3dPoint fixed_point = ann->m_plane.PointAt(text_offset_translation.x,text_offset_translation.y);
    horizonal_xform.Rotation( 
        fixed_point,
        ann->m_plane.xaxis,
        ann->m_plane.yaxis,
        ann->m_plane.zaxis,
        fixed_point,
        cameraX,
        cameraY,
        cameraZ
        );

    if ( 2 == position_style )
    {
      // leaders, radial, and diameter
      ON_2dPoint E(0.0,0.0); // end point
      ON_2dVector R(1.0,0.0); // unit vector from penultimate point to end point
      GetLeaderEndAndDirection( this, E, R );
      ON_3dVector V = R.x*m_plane.xaxis + R.y*m_plane.yaxis;
      x = V*cameraX;
      y = ( x > -ON_SQRT_EPSILON )
        ? dimstyle_textgap
        : -(dimstyle_textgap + text_line_width);
      V = y*cameraX;
      horizonal_xform.m_xform[0][3] += V.x;
      horizonal_xform.m_xform[1][3] += V.y;
      horizonal_xform.m_xform[2][3] += V.z;
    }
  }

  ON_Xform gdi_to_world;

  gdi_to_world = horizonal_xform
               * plane_to_world
               * plane_translation
               * text_centering_xform
               * gdi_to_plane;

  xform = gdi_to_world;

  return true;
}

bool ON_OBSOLETE_V5_Annotation::GetTextPoint( ON_2dPoint& text_2d_point ) const
{
  bool rc = false;
  switch ( m_type )
  {
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtTextBlock:
    text_2d_point.Set(0.0,0.0);
    rc = true;
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimLinear:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAligned:
    if ( m_userpositionedtext )
    {
      if ( m_points.Count() >= 5 )
      {
        text_2d_point = m_points[4];
        rc = true;
      }
    }
    else if ( m_points.Count() >= 3 )
    {
      text_2d_point.x = 0.5*(m_points[0].x + m_points[2].x);
      text_2d_point.y = m_points[2].y;
      rc = true;
    }
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtLeader:
    if ( m_points.Count() > 0 )
    {
      text_2d_point = *m_points.Last();
      rc = true;
    }
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimAngular:
    {
      const ON_OBSOLETE_V5_DimAngular* angular_dim = ON_OBSOLETE_V5_DimAngular::Cast(this);
      if ( angular_dim )
      {
        if ( m_userpositionedtext )
        {
          if ( m_points.Count() >= 0 )
          {
            text_2d_point = m_points[0];
          }
        }
        else
        {
          text_2d_point.x = angular_dim->m_radius*cos(angular_dim->m_angle);
          text_2d_point.y = angular_dim->m_radius*sin(angular_dim->m_angle);
          rc = true;
        }
      }
    }
    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimRadius:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimDiameter:
    // no user positioned text
    if ( m_points.Count() >= 3 )
    {
      text_2d_point = m_points[2];
      rc = true;
    }

    break;

  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtDimOrdinate:
  case ON_INTERNAL_OBSOLETE::V5_eAnnotationType::dtNothing:
    break;
  }
  return rc;
}


////////////////////////////////////////////////////////////
//
// do not copy or export this class definition.
//
class /*NEVER PUT THIS CLASS IN THE SDK*/ ON_AnnotationTextFormula : public ON_UserData
{
#if !defined(BOZO_VACCINE_699FCC4262D4488c9109F1B7A37CE926)
#error Never copy this class definition or put this definition in a header file!
#endif
  ON_OBJECT_DECLARE(ON_AnnotationTextFormula);
public:
  ON_AnnotationTextFormula();
  ~ON_AnnotationTextFormula();
  // NO! - do not add IO support to this userdata! // bool Write(ON_BinaryArchive&) const;
  // NO! - do not add IO support to this userdata! // bool Read(ON_BinaryArchive&);
  bool GetDescription(ON_wString&) override;
  // NO! - do not add IO support to this userdata! // bool Archive() const; 
  static ON_AnnotationTextFormula* Get(const ON_OBSOLETE_V5_Annotation*);
  static void Set(ON_OBSOLETE_V5_Annotation*,const wchar_t* text_formula);

  ON_wString m_text_formula;
};

#undef BOZO_VACCINE_699FCC4262D4488c9109F1B7A37CE926

ON_OBJECT_IMPLEMENT(ON_AnnotationTextFormula,ON_UserData,"699FCC42-62D4-488c-9109-F1B7A37CE926");

ON_AnnotationTextFormula::~ON_AnnotationTextFormula()
{}

ON_AnnotationTextFormula::ON_AnnotationTextFormula()
{
  m_userdata_uuid = ON_CLASS_ID(ON_AnnotationTextFormula);
  m_application_uuid = ON_opennurbs5_id;
  m_userdata_copycount = 1;
}

bool ON_AnnotationTextFormula::GetDescription( ON_wString& description )
{
  description = "Annotation Text Formula";
  return true;
}

ON_AnnotationTextFormula* ON_AnnotationTextFormula::Get(const ON_OBSOLETE_V5_Annotation* p)
{
  return (0 != p)
         ? ON_AnnotationTextFormula::Cast(p->GetUserData(ON_CLASS_ID(ON_AnnotationTextFormula)))
         : 0;
}

void ON_AnnotationTextFormula::Set(ON_OBSOLETE_V5_Annotation* p,const wchar_t* text_formula)
{
  if ( 0 != p )
  {
    ON_AnnotationTextFormula* tf = Get(p);
    if ( 0 == text_formula || 0 == text_formula[0] )
    {
      if (0 != tf )
        delete tf; 
    }
    else
    {
      if ( 0 == tf )
      {
        tf = new ON_AnnotationTextFormula();
        p->AttachUserData(tf);
      }
      tf->m_text_formula = text_formula;
    }
  }
}
//
// do not copy or export this class definition.
//
////////////////////////////////////////////////////////////

void ON_OBSOLETE_V5_Annotation::SetTextValue( const wchar_t* text_value )
{
  m_usertext = text_value; 
}

const wchar_t* ON_OBSOLETE_V5_Annotation::TextValue() const
{
  return ((const wchar_t*)m_usertext);
}

void ON_OBSOLETE_V5_Annotation::SetTextFormula( const wchar_t* text_formula )
{
  ON_AnnotationTextFormula::Set(this,text_formula);
}

const wchar_t* ON_OBSOLETE_V5_Annotation::TextFormula() const
{
  const ON_AnnotationTextFormula* tf = ON_AnnotationTextFormula::Get(this);
  return (0 != tf) ? ((const wchar_t*)tf->m_text_formula) : TextValue();
}

bool ON_BinaryArchive::Internal_WriteV2AnnotationObject(
  const ON_OBSOLETE_V5_Annotation& V5_annotation,
  const ON_3dmAnnotationContext* annotation_context
)
{
  if (m_3dm_version != 1 && m_3dm_version != 2)
  {
    ON_ERROR("m_3dm_version must be 1 or 2");
    return false;
  }


  const ON_DimStyle* dim_style = nullptr;
  int archive_dim_style_index = V5_annotation.V5_3dmArchiveDimStyleIndex();
  if ( archive_dim_style_index >= 0 && archive_dim_style_index < m_archive_dim_style_table.Count())
    dim_style = m_archive_dim_style_table[archive_dim_style_index];

  if (nullptr == dim_style)
  {
    dim_style = &ArchiveCurrentDimStyle();
    archive_dim_style_index = ArchiveCurrentDimStyleIndex();
  }

  //const int V5_3dm_archive_dim_style_index = m_manifest.ItemFromId(ON_ModelComponent::Type::DimStyle, dim_style->Id()).Index();

  m_annotation_context.SetReferencedDimStyle(dim_style,nullptr,archive_dim_style_index);
  if (nullptr == annotation_context)
    annotation_context = &m_annotation_context;
  
  ON_OBSOLETE_V2_Annotation* V2_annotation = ON_OBSOLETE_V2_Annotation::CreateFromV5Annotation(
    V5_annotation,
    annotation_context
  );
  bool rc
    = (nullptr != V2_annotation)
    ? Internal_WriteObject(*V2_annotation)
    : Internal_WriteObject(V5_annotation);
  if (nullptr != V2_annotation)
    delete V2_annotation;
  return rc;
}


ON_INTERNAL_OBSOLETE::V5_vertical_alignment ON_INTERNAL_OBSOLETE::V5VerticalAlignmentFromV5Justification(
    unsigned int v5_justification_bits
  )
{
  ON_INTERNAL_OBSOLETE::V5_vertical_alignment valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Bottom;

  const unsigned int v5_valign_mask
    = ON_OBSOLETE_V5_TextObject::eTextJustification::tjBottom
    | ON_OBSOLETE_V5_TextObject::eTextJustification::tjMiddle
    | ON_OBSOLETE_V5_TextObject::eTextJustification::tjTop;

  if (ON_OBSOLETE_V5_TextObject::eTextJustification::tjTop == (v5_justification_bits & v5_valign_mask))
    valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Top;
  else if (ON_OBSOLETE_V5_TextObject::eTextJustification::tjMiddle == (v5_justification_bits & v5_valign_mask))
    valign = ON_INTERNAL_OBSOLETE::V5_vertical_alignment::Middle;

  return valign;
}

ON_INTERNAL_OBSOLETE::V5_horizontal_alignment ON_INTERNAL_OBSOLETE::V5HorizontalAlignmentFromV5Justification(
    unsigned int v5_justification_bits
  )
{
  ON_INTERNAL_OBSOLETE::V5_horizontal_alignment halign = ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Left;

  const unsigned int v5_halign_mask
    = ON_OBSOLETE_V5_TextObject::eTextJustification::tjLeft
    | ON_OBSOLETE_V5_TextObject::eTextJustification::tjCenter
    | ON_OBSOLETE_V5_TextObject::eTextJustification::tjRight;

  if (ON_OBSOLETE_V5_TextObject::eTextJustification::tjCenter == (v5_justification_bits & v5_halign_mask))
    halign = ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Center;
  else if (ON_OBSOLETE_V5_TextObject::eTextJustification::tjRight == (v5_justification_bits & v5_halign_mask))
    halign = ON_INTERNAL_OBSOLETE::V5_horizontal_alignment::Right;

  return halign;
}



