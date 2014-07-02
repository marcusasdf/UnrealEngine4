// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "ModuleDescriptor.h"


/**
 * Simple data structure that is filled when querying information about plugins
 */
class FPluginStatus
{

public:

	/** The name of this plugin */
	FString Name;

	/** Friendly name for the plugin */
	FString FriendlyName;

	/** Internal version number (not user displayed, but valid for comparisons.) */
	int32 Version;

	/** Friendly version name */
	FString VersionName;

	/** Description of the plugin */
	FString Description;

	/** Created by name */
	FString CreatedBy;

	/** Created by URL string */
	FString CreatedByURL;

	/** Category path (dot-separated list of categories) */
	FString CategoryPath;

	/** Path to plugin directory on disk */
	FString PluginDirectory;

	/** True if plugin is currently enabled */
	bool bIsEnabled;

	/** True if plugin is enabled by default in all projects */
	bool bIsEnabledByDefault;

	/** True if the plugin is a 'built-in' engine plugin */
	bool bIsBuiltIn;

	/** Full path to the 128x128 thumbnail icon file name (or an empty string if no icon is available) */
	FString Icon128FilePath;

	/** Marks the plugin as beta in the UI */
	bool bIsBetaVersion;

	/** Whether the plugin has a content folder */
	bool bHasContentFolder;

};

/**
 * Structure holding information about a plugin content folder
 */
struct FPluginContentFolder
{
	/** Name of the plugin */
	FString Name;

	/** Virtual root path for asset paths */
	FString RootPath;

	/** Content path on disk */
	FString ContentPath;
};

/**
 * PluginManager manages available code and content extensions (both loaded and not loaded.)
 */
class IPluginManager
{

public:

	/**
	 * Static: Access singleton instance
	 *
	 * @return	Reference to the singleton object
	 */
	static PROJECTS_API IPluginManager& Get();


	/**
	 * Loads all plugins
	 *
	 * @param	LoadingPhase	Which loading phase we're loading plugin modules from.  Only modules that are configured to be
	 *							loaded at the specified loading phase will be loaded during this call.
	 */
	virtual void LoadModulesForEnabledPlugins( const ELoadingPhase::Type LoadingPhase ) = 0;

	/** Delegate type for mounting content paths.  Used internally by FPackageName code. */
	DECLARE_DELEGATE_TwoParams( FRegisterMountPointDelegate, const FString& /* Root content path */, const FString& /* Directory name */ );

	/**
	 * Sets the delegate to call to register a new content mount point.  This is used internally by the plugin manager system
	 * and should not be called by you.  This is registered at application startup by FPackageName code in CoreUObject.
	 *
	 * @param	Delegate	The delegate to that will be called when plugin manager needs to register a mount point
	 */
	virtual void SetRegisterMountPointDelegate( const FRegisterMountPointDelegate& Delegate ) = 0;

	/** 
	 * Queries whether a module is provided by a plugin
	 *
	 * @param	ModuleName	The name of the module to check
	 * @returns true if the module is supplied by a plugin
	 */
	virtual bool IsPluginModule( const FName ModuleName ) const = 0;

	/** 
	 * Checks whether modules for the enabled plugins are up to date
	 *
	 * @returns true if the enabled plugin modules are up to date
	 */
	virtual bool AreEnabledPluginModulesUpToDate( ) = 0;

	/**
	 * Gets status about all currently known plugins
	 *
	 * @return	 Array of plugin status objects
	 */
	virtual TArray< FPluginStatus > QueryStatusForAllPlugins() const = 0;

	/**
	 * Gets a list of plugin content folders
	 *
	 * @return	 Array of plugin content folders
	 */
	virtual const TArray< FPluginContentFolder >& GetPluginContentFolders() const = 0;
};
