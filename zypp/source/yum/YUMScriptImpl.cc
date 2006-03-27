/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/source/yum/YUMScriptImpl.cc
*/

#include "zypp/source/yum/YUMScriptImpl.h"
#include "zypp/Arch.h"
#include "zypp/Edition.h"

#include <fstream>


using namespace std;
using namespace zypp::detail;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace source
  { /////////////////////////////////////////////////////////////////
    namespace yum
    {

      ///////////////////////////////////////////////////////////////////
      //
      //        CLASS NAME : YUMScriptImpl
      //
      ///////////////////////////////////////////////////////////////////

      /** Default ctor
      */
      YUMScriptImpl::YUMScriptImpl(
	Source_Ref source_r,
	const zypp::parser::yum::YUMPatchScript & parsed
      )
      : _source(source_r)
      , _do_script(parsed.do_script)
      , _undo_script(parsed.undo_script)
      , _do_location(parsed.do_location)
      , _undo_location(parsed.undo_location)
      , _do_media(1)
      , _undo_media(1)
      {
	unsigned do_media = strtol(parsed.do_media.c_str(), 0, 10);
	if (do_media > 0)
	  _do_media = do_media;
	unsigned undo_media = strtol(parsed.undo_media.c_str(), 0, 10);
	if (undo_media > 0)
	  _undo_media = undo_media;
      }

      Pathname YUMScriptImpl::do_script() const {
	if (_do_script != "")
	{
	  _tmp_file = filesystem::TmpFile();
	  Pathname pth = _tmp_file.path();
	  ofstream st(pth.asString().c_str());
	  st << _undo_script << endl;
	  return pth;
	}
	else if (_do_location != "" && _do_location != "/")
	{
	  return source().provideFile(_do_location, _do_media);
	}
	else
	{
	  return Pathname();
	}
      }
      /** Get the script to undo the change */
     Pathname YUMScriptImpl::undo_script() const {
	if (_undo_script != "")
	{
	  _tmp_file = filesystem::TmpFile();
	  Pathname pth = _tmp_file.path();
	  ofstream st(pth.asString().c_str());
	  st << _undo_script << endl;
	  return pth;
	}
	else if (_undo_location != "" && _undo_location != "/")
	{
	  return source().provideFile(_undo_location, _undo_media);
	}
	else return Pathname();
      }
      /** Check whether script to undo the change is available */
      bool YUMScriptImpl::undo_available() const {
	return _undo_script != ""
	  || (_undo_location != "" && _undo_location != "/");
      }
      TranslatedText YUMScriptImpl::summary() const
      { return ResObjectImplIf::summary(); }

      TranslatedText YUMScriptImpl::description() const
      { return ResObjectImplIf::description(); }

      Text YUMScriptImpl::insnotify() const
      { return ResObjectImplIf::insnotify(); }

      Text YUMScriptImpl::delnotify() const
      { return ResObjectImplIf::delnotify(); }

      bool YUMScriptImpl::providesSources() const
      { return ResObjectImplIf::providesSources(); }

      Label YUMScriptImpl::instSrcLabel() const
      { return ResObjectImplIf::instSrcLabel(); }

      Vendor YUMScriptImpl::instSrcVendor() const
      { return ResObjectImplIf::instSrcVendor(); }

      Source_Ref YUMScriptImpl::source() const
      { return _source; }



    } // namespace yum
    /////////////////////////////////////////////////////////////////
  } // namespace source
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
