/*MT*
    
    MediaTomb - http://www.mediatomb.cc/
    
    config_manager.h - this file is part of MediaTomb.
    
    Copyright (C) 2005 Gena Batyan <bgeradz@mediatomb.cc>,
                       Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>
    
    Copyright (C) 2006-2010 Gena Batyan <bgeradz@mediatomb.cc>,
                            Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>,
                            Leonhard Wimmer <leo@mediatomb.cc>
    
    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation.
    
    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    version 2 along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
    
    $Id$
*/

/// \file config_manager.h
///\brief Definitions of the ConfigManager class.

#ifndef __CONFIG_MANAGER_H__
#define __CONFIG_MANAGER_H__

#include <memory>
#include <pugixml.hpp>

#include "autoscan.h"
#include "common.h"
#include "config_options.h"

#include "transcoding/transcoding.h"
#ifdef ONLINE_SERVICES
#include "onlineservice/online_service.h"
#endif
typedef enum {
    CFG_SERVER_PORT = 0,
    CFG_SERVER_IP,
    CFG_SERVER_NETWORK_INTERFACE,
    CFG_SERVER_NAME,
    CFG_SERVER_MANUFACTURER,
    CFG_SERVER_MANUFACTURER_URL,
    CFG_SERVER_MODEL_NAME,
    CFG_SERVER_MODEL_DESCRIPTION,
    CFG_SERVER_MODEL_NUMBER,
    CFG_SERVER_MODEL_URL,
    CFG_SERVER_SERIAL_NUMBER,
    CFG_SERVER_PRESENTATION_URL,
    CFG_SERVER_APPEND_PRESENTATION_URL_TO,
    CFG_SERVER_UDN,
    CFG_SERVER_HOME,
    CFG_SERVER_TMPDIR,
    CFG_SERVER_WEBROOT,
    CFG_SERVER_SERVEDIR,
    CFG_SERVER_ALIVE_INTERVAL,
    CFG_SERVER_EXTEND_PROTOCOLINFO,
    CFG_SERVER_EXTEND_PROTOCOLINFO_CL_HACK,
    CFG_SERVER_EXTEND_PROTOCOLINFO_SM_HACK,
    CFG_SERVER_EXTEND_PROTOCOLINFO_DLNA_SEEK,
    CFG_SERVER_HIDE_PC_DIRECTORY,
    CFG_SERVER_BOOKMARK_FILE,
    CFG_SERVER_CUSTOM_HTTP_HEADERS,
    CFG_SERVER_UPNP_TITLE_AND_DESC_STRING_LIMIT,
    CFG_SERVER_UI_ENABLED,
    CFG_SERVER_UI_POLL_INTERVAL,
    CFG_SERVER_UI_POLL_WHEN_IDLE,
    CFG_SERVER_UI_ACCOUNTS_ENABLED,
    CFG_SERVER_UI_ACCOUNT_LIST,
    CFG_SERVER_UI_SESSION_TIMEOUT,
    CFG_SERVER_UI_DEFAULT_ITEMS_PER_PAGE,
    CFG_SERVER_UI_ITEMS_PER_PAGE_DROPDOWN,
    CFG_SERVER_UI_SHOW_TOOLTIPS,
    CFG_SERVER_STORAGE_DRIVER,
#ifdef HAVE_SQLITE3
    CFG_SERVER_STORAGE_SQLITE_DATABASE_FILE,
    CFG_SERVER_STORAGE_SQLITE_SYNCHRONOUS,
    CFG_SERVER_STORAGE_SQLITE_RESTORE,
    CFG_SERVER_STORAGE_SQLITE_BACKUP_ENABLED,
    CFG_SERVER_STORAGE_SQLITE_BACKUP_INTERVAL,
#endif
#ifdef HAVE_MYSQL
    CFG_SERVER_STORAGE_MYSQL_HOST,
    CFG_SERVER_STORAGE_MYSQL_PORT,
    CFG_SERVER_STORAGE_MYSQL_USERNAME,
    CFG_SERVER_STORAGE_MYSQL_SOCKET,
    CFG_SERVER_STORAGE_MYSQL_PASSWORD,
    CFG_SERVER_STORAGE_MYSQL_DATABASE,
#endif
#if defined(HAVE_FFMPEG) && defined(HAVE_FFMPEGTHUMBNAILER)
    CFG_SERVER_EXTOPTS_FFMPEGTHUMBNAILER_ENABLED,
    CFG_SERVER_EXTOPTS_FFMPEGTHUMBNAILER_THUMBSIZE,
    CFG_SERVER_EXTOPTS_FFMPEGTHUMBNAILER_SEEK_PERCENTAGE,
    CFG_SERVER_EXTOPTS_FFMPEGTHUMBNAILER_FILMSTRIP_OVERLAY,
    CFG_SERVER_EXTOPTS_FFMPEGTHUMBNAILER_WORKAROUND_BUGS,
    CFG_SERVER_EXTOPTS_FFMPEGTHUMBNAILER_IMAGE_QUALITY,
    CFG_SERVER_EXTOPTS_FFMPEGTHUMBNAILER_CACHE_DIR_ENABLED,
    CFG_SERVER_EXTOPTS_FFMPEGTHUMBNAILER_CACHE_DIR,
#endif
    CFG_SERVER_EXTOPTS_MARK_PLAYED_ITEMS_ENABLED,
    CFG_SERVER_EXTOPTS_MARK_PLAYED_ITEMS_STRING_MODE_PREPEND,
    CFG_SERVER_EXTOPTS_MARK_PLAYED_ITEMS_STRING,
    CFG_SERVER_EXTOPTS_MARK_PLAYED_ITEMS_SUPPRESS_CDS_UPDATES,
    CFG_SERVER_EXTOPTS_MARK_PLAYED_ITEMS_CONTENT_LIST,
#ifdef HAVE_LASTFMLIB
    CFG_SERVER_EXTOPTS_LASTFM_ENABLED,
    CFG_SERVER_EXTOPTS_LASTFM_USERNAME,
    CFG_SERVER_EXTOPTS_LASTFM_PASSWORD,
#endif
    CFG_IMPORT_HIDDEN_FILES,
    CFG_IMPORT_FILESYSTEM_CHARSET,
    CFG_IMPORT_METADATA_CHARSET,
    CFG_IMPORT_PLAYLIST_CHARSET,
#ifdef HAVE_JS
    CFG_IMPORT_SCRIPTING_CHARSET,
    CFG_IMPORT_SCRIPTING_COMMON_SCRIPT,
    CFG_IMPORT_SCRIPTING_PLAYLIST_SCRIPT,
    CFG_IMPORT_SCRIPTING_PLAYLIST_SCRIPT_LINK_OBJECTS,
    CFG_IMPORT_SCRIPTING_IMPORT_SCRIPT,
#endif // JS
    CFG_IMPORT_SCRIPTING_VIRTUAL_LAYOUT_TYPE,
#ifdef HAVE_MAGIC
    CFG_IMPORT_MAGIC_FILE,
#endif
    CFG_IMPORT_AUTOSCAN_TIMED_LIST,
#ifdef HAVE_INOTIFY
    CFG_IMPORT_AUTOSCAN_USE_INOTIFY,
    CFG_IMPORT_AUTOSCAN_INOTIFY_LIST,
#endif
    CFG_IMPORT_MAPPINGS_IGNORE_UNKNOWN_EXTENSIONS,
    CFG_IMPORT_MAPPINGS_EXTENSION_TO_MIMETYPE_CASE_SENSITIVE,
    CFG_IMPORT_MAPPINGS_EXTENSION_TO_MIMETYPE_LIST,
    CFG_IMPORT_MAPPINGS_MIMETYPE_TO_UPNP_CLASS_LIST,
    CFG_IMPORT_MAPPINGS_MIMETYPE_TO_CONTENTTYPE_LIST,
#ifdef HAVE_LIBEXIF
    CFG_IMPORT_LIBOPTS_EXIF_AUXDATA_TAGS_LIST,
#endif
#ifdef HAVE_EXIV2
    CFG_IMPORT_LIBOPTS_EXIV2_AUXDATA_TAGS_LIST,
#endif
#if defined(HAVE_TAGLIB)
    CFG_IMPORT_LIBOPTS_ID3_AUXDATA_TAGS_LIST,
#endif
    CFG_TRANSCODING_PROFILE_LIST,
#ifdef HAVE_CURL
    CFG_EXTERNAL_TRANSCODING_CURL_BUFFER_SIZE,
    CFG_EXTERNAL_TRANSCODING_CURL_FILL_SIZE,
#endif //HAVE_CURL
#ifdef SOPCAST
    CFG_ONLINE_CONTENT_SOPCAST_ENABLED,
    CFG_ONLINE_CONTENT_SOPCAST_REFRESH,
    CFG_ONLINE_CONTENT_SOPCAST_UPDATE_AT_START,
    CFG_ONLINE_CONTENT_SOPCAST_PURGE_AFTER,
#endif
#ifdef ATRAILERS
    CFG_ONLINE_CONTENT_ATRAILERS_ENABLED,
    CFG_ONLINE_CONTENT_ATRAILERS_REFRESH,
    CFG_ONLINE_CONTENT_ATRAILERS_UPDATE_AT_START,
    CFG_ONLINE_CONTENT_ATRAILERS_PURGE_AFTER,
    CFG_ONLINE_CONTENT_ATRAILERS_RESOLUTION,
#endif
#if defined(HAVE_FFMPEG)
    CFG_IMPORT_LIBOPTS_FFMPEG_AUXDATA_TAGS_LIST,
#endif
    CFG_MAX
} config_option_t;

class ConfigManager {
public:
    ConfigManager(fs::path filename,
        const fs::path& userhome, const fs::path& config_dir,
        fs::path prefix_dir, fs::path magic_file,
        std::string ip, std::string interface, int port,
        bool debug_logging);
    virtual ~ConfigManager();

    /// \brief Returns the name of the config file that was used to launch the server.
    inline fs::path getConfigFilename() { return filename; }

    void load(const fs::path& filename, const fs::path& userHome);

    /// \brief returns a config option of type std::string
    /// \param option option to retrieve.
    std::string getOption(config_option_t option);

    /// \brief returns a config option of type int
    /// \param option option to retrieve.
    int getIntOption(config_option_t option);

    /// \brief returns a config option of type bool
    /// \param option option to retrieve.
    bool getBoolOption(config_option_t option);

    /// \brief returns a config option of type Dictionary
    /// \param option option to retrieve.
    std::map<std::string, std::string> getDictionaryOption(config_option_t option);

    /// \brief returns a config option of type Array of StringBase
    /// \param option option to retrieve.
    std::vector<std::string> getStringArrayOption(config_option_t option);

    /// \brief returns a config option of type AutoscanList
    /// \param option to retrieve
    std::shared_ptr<AutoscanList> getAutoscanListOption(config_option_t option);

    /// \brief returns a config option of type TranscodingProfileList
    /// \param option to retrieve
    std::shared_ptr<TranscodingProfileList> getTranscodingProfileListOption(config_option_t option);

    static bool isDebugLogging() { return debug_logging; };

    /// \brief Creates a html file that is a redirector to the current server i
    /// instance
    void writeBookmark(const std::string& ip, const std::string& port);
    void emptyBookmark();

protected:
    fs::path filename;
    fs::path prefix_dir;
    fs::path magic_file;
    std::string ip;
    std::string interface;
    int port;
    static bool debug_logging;

    std::unique_ptr<pugi::xml_document> xmlDoc;

    std::unique_ptr<std::vector<std::shared_ptr<ConfigOption>>> options;

    /// \brief Returns a config option with the given xpath, if option does not exist a default value is returned.
    /// \param xpath option xpath
    /// \param def default value if option not found
    ///
    /// The xpath parameter has XPath syntax:
    /// "/path/to/option" will return the text value of the given "option" element
    /// "/path/to/option/attribute::attr" will return the value of the attribute "attr"
    std::string getOption(std::string xpath, std::string def);

    /// \brief same as getOption but returns an integer value of the option
    int getIntOption(std::string xpath, int def);

    /// \brief Returns a config option with the given xpath, an exception is raised if option does not exist.
    /// \param xpath option xpath.
    ///
    /// The xpath parameter has XPath syntax:
    /// "/path/to/option" will return the text value of the given "option" element
    /// "/path/to/option/attribute::attr" will return the value of the attribute "attr"
    std::string getOption(std::string xpath);

    /// \brief Returns an integer value of the option with the given xpath, an exception is raised if option does not exist.
    /// \param xpath option xpath.
    ///
    /// The xpath parameter has XPath syntax:
    /// "/path/to/option" will return the text value of the given "option" element
    /// "/path/to/option/attribute::attr" will return the value of the attribute "attr"
    int getIntOption(std::string xpath);

    /// \brief Returns a config XML element with the given xpath, an exception is raised if element does not exist.
    /// \param xpath option xpath.
    ///
    /// The xpath parameter has XPath syntax:
    /// "/path/to/element" will return the text value of the given "element" element
    pugi::xml_node getElement(std::string xpath);

    /// \brief resolve path against home, an exception is raised if path does not exist on filesystem.
    /// \param path path to be resolved
    /// \param isFile file or directory
    /// \param exists must file exist
    fs::path resolvePath(fs::path path, bool isFile = false, bool exists = true);

    /// \brief Creates a dictionary from an XML nodeset.
    /// \param element starting element of the nodeset.
    /// \param nodeName name of each node in the set
    /// \param keyAttr attribute name to be used as a key
    /// \param valAttr attribute name to be used as value
    ///
    /// The basic idea is the following:
    /// You have a piece of XML that looks like this
    /// <some-section>
    ///    <map from="1" to="2"/>
    ///    <map from="3" to="4"/>
    /// </some-section>
    ///
    /// This function will create a dictionary with the following
    /// key:value paris: "1":"2", "3":"4"
    std::map<std::string, std::string> createDictionaryFromNode(const pugi::xml_node& element,
        const std::string& nodeName, const std::string& keyAttr, const std::string& valAttr, bool tolower = false);

    /// \brief Creates an array of AutoscanDirectory objects from a XML nodeset.
    /// \param element starting element of the nodeset.
    /// \param scanmode add only directories with the specified scanmode to the array
    std::shared_ptr<AutoscanList> createAutoscanListFromNode(const std::shared_ptr<Storage>& storage, const pugi::xml_node& element,
        ScanMode scanmode);

    /// \brief Creates ab aray of TranscodingProfile objects from an XML
    /// nodeset.
    /// \param element starting element of the nodeset.
    std::shared_ptr<TranscodingProfileList> createTranscodingProfileListFromNode(const pugi::xml_node& element);

    /// \brief Creates an array of strings from an XML nodeset.
    /// \param element starting element of the nodeset.
    /// \param nodeName name of each node in the set
    /// \param attrName name of the attribute, the value of which shouldbe extracted
    ///
    /// Similar to \fn createDictionaryFromNodeset() this one extracts
    /// data from the following XML:
    /// <some-section>
    ///     <tag attr="data"/>
    ///     <tag attr="otherdata"/>
    /// <some-section>
    ///
    /// This function will create an array like that: ["data", "otherdata"]
    std::vector<std::string> createArrayFromNode(const pugi::xml_node& element, const std::string& nodeName, const std::string& attrName);

    void dumpOptions();
};

#endif // __CONFIG_MANAGER_H__
