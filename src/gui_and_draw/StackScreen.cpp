//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//
//
//////////////////////////////////////////////////////////////////////

#include "StackScreen.h"
#include "ScreenMgr.h"
#include "StackGeom.h"

using namespace vsp;

//==== Constructor ====//
StackScreen::StackScreen( ScreenMgr* mgr ) : ChevronScreen( mgr, 460, 800, "Stack" )
{
    m_CurrDisplayGroup = nullptr;

    Fl_Group* design_tab = AddTab( "Design", 4 );

    Fl_Group* design_group = AddSubGroup( design_tab, 5 );

    m_DesignLayout.SetGroupAndScreen( design_group, this );
    m_DesignLayout.AddDividerBox( "Design" );

    m_DesignLayout.AddYGap();
    m_DesignLayout.AddDividerBox( "Design Policy" );
    m_DesignPolicyChoice.AddItem( "FREE" );
    m_DesignPolicyChoice.AddItem( "LOOP" );
    m_DesignLayout.AddChoice( m_DesignPolicyChoice, "XSec Order: " );

    m_DesignLayout.AddYGap();
    m_DesignLayout.AddDividerBox( "Tip Treatment" );

    m_NoseCapTypeChoice.AddItem( "None", vsp::NO_END_CAP );
    m_NoseCapTypeChoice.AddItem( "Flat", vsp::FLAT_END_CAP );
    m_NoseCapTypeChoice.AddItem( "Round", vsp::ROUND_END_CAP );
    m_NoseCapTypeChoice.AddItem( "Edge", vsp::EDGE_END_CAP );
    m_NoseCapTypeChoice.AddItem( "Sharp", vsp::SHARP_END_CAP );
    m_DesignLayout.AddChoice(m_NoseCapTypeChoice, "Nose Cap Type");

    m_DesignLayout.AddSlider( m_NoseCapLenSlider, "Length", 1, "%6.5f" );
    m_DesignLayout.AddSlider( m_NoseCapOffsetSlider, "Offset", 1, "%6.5f" );
    m_DesignLayout.AddSlider( m_NoseCapStrengthSlider, "Strength", 1, "%6.5f" );
    m_DesignLayout.AddButton( m_NoseCapSweepFlagButton, "Sweep Stretch" );

    m_DesignLayout.AddYGap();

    m_TailCapTypeChoice.AddItem( "None", vsp::NO_END_CAP );
    m_TailCapTypeChoice.AddItem( "Flat", vsp::FLAT_END_CAP );
    m_TailCapTypeChoice.AddItem( "Round", vsp::ROUND_END_CAP );
    m_TailCapTypeChoice.AddItem( "Edge", vsp::EDGE_END_CAP );
    m_TailCapTypeChoice.AddItem( "Sharp", vsp::SHARP_END_CAP );
    m_DesignLayout.AddChoice(m_TailCapTypeChoice, "Tail Cap Type");

    m_DesignLayout.AddSlider( m_TailCapLenSlider, "Length", 1, "%6.5f" );
    m_DesignLayout.AddSlider( m_TailCapOffsetSlider, "Offset", 1, "%6.5f" );
    m_DesignLayout.AddSlider( m_TailCapStrengthSlider, "Strength", 1, "%6.5f" );
    m_DesignLayout.AddButton( m_TailCapSweepFlagButton, "Sweep Stretch" );

    m_DesignLayout.AddYGap();

    m_DesignLayout.AddSlider( m_CapTessSlider, "Cap Tess", 10, "%3.0f" );

    BuildEngineGUI( m_DesignLayout );

    // Xsec layout after index selector has been defined in base class
    m_XSecLayout.SetFitWidthFlag( false );
    m_XSecLayout.SetSameLineFlag( true );
    m_XSecLayout.SetButtonWidth( ( m_XSecLayout.GetRemainX() - 30 ) / 4 );
    m_XSecLayout.AddButton( m_InsertXSec, "Insert" );
    m_XSecLayout.AddX( 10 );
    m_XSecLayout.AddButton( m_CutXSec, "Cut" );
    m_XSecLayout.AddX( 10 );
    m_XSecLayout.AddButton( m_CopyXSec, "Copy" );
    m_XSecLayout.AddX( 10 );
    m_XSecLayout.AddButton( m_PasteXSec, "Paste" );
    m_XSecLayout.ForceNewLine();

    m_XSecLayout.SetFitWidthFlag( true );
    m_XSecLayout.SetSameLineFlag( false );

    m_XSecLayout.AddYGap();
    m_XSecLayout.InitWidthHeightVals();
    int bw = m_XSecLayout.GetButtonWidth() + 5;
    m_XSecLayout.SetButtonWidth( bw );

    m_XSecLayout.AddSlider( m_SectUTessSlider, "Num U", 20, " %5.0f" );
    m_XSecLayout.SetFitWidthFlag( true );
    m_XSecLayout.SetSameLineFlag( true );
    m_XSecLayout.AddSlider( m_FwdClusterSlider, "Fwd. Cluster", 1, "%6.5f", m_XSecLayout.GetW() * 0.5 );
    m_XSecLayout.AddSlider( m_AftClusterSlider, "Aft Cluster", 1, "%6.5f" );
    m_XSecLayout.ForceNewLine();
    m_XSecLayout.AddYGap();

    m_XSecLayout.SetFitWidthFlag( false );
    m_XSecLayout.SetSameLineFlag( true );
    m_XSecLayout.AddLabel( "Coord System:", m_XSecLayout.GetW() - 2 * m_XSecLayout.GetInputWidth() );
    m_XSecLayout.SetButtonWidth( m_XSecLayout.GetInputWidth() );
    m_XSecLayout.AddButton( m_XSecRelativeToggle, "Rel" );
    m_XSecLayout.AddButton( m_XSecAbsoluteToggle, "Abs" );
    m_XSecLayout.ForceNewLine();

    m_XSecAbsRelToggle.Init( this );
    m_XSecAbsRelToggle.AddButton( m_XSecAbsoluteToggle.GetFlButton() );
    m_XSecAbsRelToggle.AddButton( m_XSecRelativeToggle.GetFlButton() );

    m_XSecLayout.SetFitWidthFlag( true );
    m_XSecLayout.SetSameLineFlag( false );
    m_XSecLayout.SetButtonWidth( bw );
    m_XSecLayout.AddSlider( m_XSecXDeltaSlider, "Delta X", 10.0, "%6.5f" );
    m_XSecLayout.AddSlider( m_XSecYDeltaSlider, "Delta Y", 10.0, "%6.5f" );
    m_XSecLayout.AddSlider( m_XSecZDeltaSlider, "Delta Z", 10.0, "%6.5f" );
    m_XSecLayout.AddYGap();


    m_XSecLayout.AddSlider( m_XSecXRotSlider, "Rot X", 90.0, "%6.5f" );
    m_XSecLayout.AddSlider( m_XSecYRotSlider, "Rot Y", 90.0, "%6.5f" );
    m_XSecLayout.AddSlider( m_XSecZRotSlider, "Rot Z", 90.0, "%6.5f" );

    m_XSecLayout.SetFitWidthFlag( true );
    m_XSecLayout.SetSameLineFlag( true );
    m_XSecLayout.AddSlider( m_XSecSpinSlider, "Spin",  2.0, "%6.5f", m_XSecLayout.GetW() * 0.5 );
    m_XSecLayout.AddSlider( m_VAlignSlider, "V Align",  2.0, "%6.5f" );
    m_XSecLayout.ForceNewLine();
    m_XSecLayout.AddYGap();

    AddXSecLayout();

}

//==== Show Pod Screen ====//
StackScreen::~StackScreen()
{
}

//==== Show Pod Screen ====//
void StackScreen::Show()
{
    if ( Update() )
    {
        ChevronScreen::Show();
    }
}

//==== Update Pod Screen ====//
bool StackScreen::Update()
{
    assert( m_ScreenMgr );

    Geom* geom_ptr = m_ScreenMgr->GetCurrGeom();
    if ( !geom_ptr || geom_ptr->GetType().m_Type != STACK_GEOM_TYPE )
    {
        Hide();
        return false;
    }

    ChevronScreen::Update();
    m_NumUSlider.Deactivate();

    StackGeom* stackgeom_ptr = dynamic_cast< StackGeom* >( geom_ptr );
    assert( stackgeom_ptr );

    m_DesignPolicyChoice.Update( stackgeom_ptr->m_OrderPolicy.GetID() );

    m_NoseCapTypeChoice.Update( stackgeom_ptr->m_CapUMinOption.GetID() );
    m_TailCapTypeChoice.Update( stackgeom_ptr->m_CapUMaxOption.GetID() );

    m_CapTessSlider.Update( stackgeom_ptr->m_CapUMinTess.GetID() );

    m_NoseCapLenSlider.Update( stackgeom_ptr->m_CapUMinLength.GetID() );
    m_NoseCapOffsetSlider.Update( stackgeom_ptr->m_CapUMinOffset.GetID() );
    m_NoseCapStrengthSlider.Update( stackgeom_ptr->m_CapUMinStrength.GetID() );
    m_NoseCapSweepFlagButton.Update( stackgeom_ptr->m_CapUMinSweepFlag.GetID() );

    UpdateCapControls( stackgeom_ptr->m_CapUMinOption(), m_NoseCapLenSlider, m_NoseCapOffsetSlider, m_NoseCapStrengthSlider, m_NoseCapSweepFlagButton );

    m_TailCapLenSlider.Update( stackgeom_ptr->m_CapUMaxLength.GetID() );
    m_TailCapOffsetSlider.Update( stackgeom_ptr->m_CapUMaxOffset.GetID() );
    m_TailCapStrengthSlider.Update( stackgeom_ptr->m_CapUMaxStrength.GetID() );
    m_TailCapSweepFlagButton.Update( stackgeom_ptr->m_CapUMaxSweepFlag.GetID() );

    UpdateCapControls( stackgeom_ptr->m_CapUMaxOption(), m_TailCapLenSlider, m_TailCapOffsetSlider, m_TailCapStrengthSlider, m_TailCapSweepFlagButton );

    //==== XSec Index Display ===//
    int xsid = stackgeom_ptr->m_ActiveXSec();
    m_XSecIndexSelector.Update( stackgeom_ptr->m_ActiveXSec.GetID() );

    StackXSec* xs = ( StackXSec* ) stackgeom_ptr->GetXSec( xsid );
    if ( xs )
    {
        bool firstxs = xsid == 0;
        bool lastxs = xsid == ( stackgeom_ptr->GetXSecSurf( 0 )->NumXSec() - 1 );
        bool nextlastxs = xsid == ( stackgeom_ptr->GetXSecSurf( 0 )->NumXSec() - 2 );

        m_SectUTessSlider.Update( xs->m_SectTessU.GetID() );
        m_FwdClusterSlider.Update( xs->m_FwdCluster.GetID() );
        m_AftClusterSlider.Update( xs->m_AftCluster.GetID() );

        // Activate these before Updating Rel/Abs (which also deactivates).
        m_XSecAbsRelToggle.Activate();
        m_SectUTessSlider.Activate();
        m_FwdClusterSlider.Activate();
        m_AftClusterSlider.Activate();
        m_XSecXDeltaSlider.Activate();
        m_XSecYDeltaSlider.Activate();
        m_XSecZDeltaSlider.Activate();
        m_XSecXRotSlider.Activate();
        m_XSecYRotSlider.Activate();
        m_XSecZRotSlider.Activate();
        m_XSecSpinSlider.Activate();
        m_VAlignSlider.Activate();

        m_XSecAbsRelToggle.Update( xs->m_XSAbsRelFlag.GetID() );
        if ( xs->m_XSAbsRelFlag() ==  vsp::REL )
        {
            m_XSecXDeltaSlider.Update( 1, xs->m_XDelta.GetID(), xs->m_XAbs.GetID() );
            m_XSecYDeltaSlider.Update( 1, xs->m_YDelta.GetID(), xs->m_YAbs.GetID() );
            m_XSecZDeltaSlider.Update( 1, xs->m_ZDelta.GetID(), xs->m_ZAbs.GetID() );
            m_XSecXRotSlider.Update( 1, xs->m_XRotate.GetID(), xs->m_XRotateAbs.GetID() );
            m_XSecYRotSlider.Update( 1, xs->m_YRotate.GetID(), xs->m_YRotateAbs.GetID() );
            m_XSecZRotSlider.Update( 1, xs->m_ZRotate.GetID(), xs->m_ZRotateAbs.GetID() );
        }
        else
        {
            m_XSecXDeltaSlider.Update( 2, xs->m_XDelta.GetID(), xs->m_XAbs.GetID() );
            m_XSecYDeltaSlider.Update( 2, xs->m_YDelta.GetID(), xs->m_YAbs.GetID() );
            m_XSecZDeltaSlider.Update( 2, xs->m_ZDelta.GetID(), xs->m_ZAbs.GetID() );
            m_XSecXRotSlider.Update( 2, xs->m_XRotate.GetID(), xs->m_XRotateAbs.GetID() );
            m_XSecYRotSlider.Update( 2, xs->m_YRotate.GetID(), xs->m_YRotateAbs.GetID() );
            m_XSecZRotSlider.Update( 2, xs->m_ZRotate.GetID(), xs->m_ZRotateAbs.GetID() );
        }

        m_XSecSpinSlider.Update( xs->m_Spin.GetID() );
        m_VAlignSlider.Update( xs->m_VAlign.GetID() );

        if ( firstxs )
        {
            m_XSecAbsRelToggle.Deactivate();
            m_SectUTessSlider.Deactivate();
            m_FwdClusterSlider.Deactivate();
            m_AftClusterSlider.Deactivate();
            m_XSecXDeltaSlider.Deactivate();
            m_XSecYDeltaSlider.Deactivate();
            m_XSecZDeltaSlider.Deactivate();
            m_XSecXRotSlider.Deactivate();
            m_XSecYRotSlider.Deactivate();
            m_XSecZRotSlider.Deactivate();
        }

        if ( lastxs && stackgeom_ptr->m_OrderPolicy() == StackGeom::STACK_LOOP)
        {
            m_XSecAbsRelToggle.Deactivate();
            m_XSecXDeltaSlider.Deactivate();
            m_XSecYDeltaSlider.Deactivate();
            m_XSecZDeltaSlider.Deactivate();
            m_XSecXRotSlider.Deactivate();
            m_XSecYRotSlider.Deactivate();
            m_XSecZRotSlider.Deactivate();
            m_XSecSpinSlider.Deactivate();
            m_VAlignSlider.Deactivate();
        }

        XSecCurve* xsc = xs->GetXSecCurve();
        if ( xsc )
        {
            // Special considerations for loop policy
            if ( lastxs && stackgeom_ptr->m_OrderPolicy() == StackGeom::STACK_LOOP )
            {
                m_XSecTypeChoice.Deactivate();
                m_ShowXSecButton.Deactivate();
                m_ConvertCEDITButton.Deactivate();
            }
            else
            {
                m_XSecTypeChoice.Activate();
                m_ShowXSecButton.Activate();
                m_ConvertCEDITButton.Activate();
            }

            if ( lastxs && stackgeom_ptr->m_OrderPolicy() == StackGeom::STACK_LOOP )
            {
                DisplayGroup ( nullptr);
            }

        }
    }
    return true;
}

void StackScreen::GuiDeviceCallBack( GuiDevice* gui_device )
{
    //==== Find Fuselage Ptr ====//
    Geom* geom_ptr = m_ScreenMgr->GetCurrGeom();
    if ( !geom_ptr || geom_ptr->GetType().m_Type != STACK_GEOM_TYPE )
    {
        return;
    }
    StackGeom* stackgeom_ptr = dynamic_cast< StackGeom* >( geom_ptr );
    assert( stackgeom_ptr );

    if ( gui_device == &m_CutXSec )
    {
        stackgeom_ptr->CutActiveXSec();
    }
    else if ( gui_device == &m_CopyXSec   )
    {
        stackgeom_ptr->CopyActiveXSec();
    }
    else if ( gui_device == &m_PasteXSec  )
    {
        stackgeom_ptr->PasteActiveXSec();
    }
    else if ( gui_device == &m_InsertXSec  )
    {
        stackgeom_ptr->InsertXSec( );
    }

    ChevronScreen::GuiDeviceCallBack( gui_device );
}

//==== Fltk  Callbacks ====//
void StackScreen::CallBack( Fl_Widget *w )
{
    ChevronScreen::CallBack( w );
}

