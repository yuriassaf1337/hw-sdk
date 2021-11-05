#pragma once
#define VENGINE_CLIENT_INTERFACE_VERSION _( "VEngineClient014" )

// need to do some basic math includes first.

/*
class iv_engine_client
{
public:

    virtual int					GetIntersectingSurfaces(
                                    const model_t *model,
                                    const Vector &vCenter,
                                    const float radius,
                                    const bool bOnlyVisibleSurfaces,	// Only return surfaces visible to vCenter.
                                    SurfInfo *pInfos,
                                    const int nMaxInfos) = 0;

    // Get the lighting intensivty for a specified point
    // If bClamp is specified, the resulting Vector is restricted to the 0.0 to 1.0 for each element
    virtual Vector				GetLightForPoint(const Vector &pos, bool bClamp) = 0;

    // Traces the line and reports the material impacted as well as the lighting information for the impact point
    virtual IMaterial			*TraceLineMaterialAndLighting( const Vector &start, const Vector &end,
                                    Vector &diffuseLightColor, Vector& baseColor ) = 0;

    // Given an input text buffer data pointer, parses a single token into the variable token and returns the new
    //  reading position
    virtual const char			*ParseFile( const char *data, char *token, int maxlen ) = 0;
    virtual bool				CopyLocalFile( const char *source, const char *destination ) = 0;

    // Gets the dimensions of the game window
    virtual void				GetScreenSize( int& width, int& height ) = 0;

    // Forwards szCmdString to the server, sent reliably if bReliable is set
    virtual void				ServerCmd( const char *szCmdString, bool bReliable = true ) = 0;
    // Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
    // Note: Calls to this are checked against FCVAR_CLIENTCMD_CAN_EXECUTE (if that bit is not set, then this function can't change it).
    //       Call ClientCmd_Unrestricted to have access to FCVAR_CLIENTCMD_CAN_EXECUTE vars.
    virtual void				ClientCmd( const char *szCmdString ) = 0;

    // Fill in the player info structure for the specified player index (name, model, etc.)
    virtual bool				GetPlayerInfo( int ent_num, player_info_t *pinfo ) = 0;

    // Retrieve the player entity number for a specified userID
    virtual int					GetPlayerForUserID( int userID ) = 0;

    // Retrieves text message system information for the specified message by name
    virtual client_textmessage_t *TextMessageGet( const char *pName ) = 0;

    // Returns true if the console is visible
    virtual bool				Con_IsVisible( void ) = 0;

    // Get the entity index of the local player
    virtual int					GetLocalPlayer( void ) = 0;

    // Client DLL is hooking a model, loads the model into memory and returns  pointer to the model_t
    virtual const model_t		*LoadModel( const char *pName, bool bProp = false ) = 0;

    // Get the exact server timesstamp ( server time ) from the last message received from the server
    virtual float				GetLastTimeStamp( void ) = 0;

    // Given a CAudioSource (opaque pointer), retrieve the underlying CSentence object ( stores the words, phonemes, and close
    //  captioning data )
    virtual CSentence			*GetSentence( CAudioSource *pAudioSource ) = 0;
    // Given a CAudioSource, determines the length of the underlying audio file (.wav, .mp3, etc.)
    virtual float				GetSentenceLength( CAudioSource *pAudioSource ) = 0;
    // Returns true if the sound is streaming off of the hard disk (instead of being memory resident)
    virtual bool				IsStreaming( CAudioSource *pAudioSource ) const = 0;

    // Copy current view orientation into va
    virtual void				GetViewAngles( QAngle& va ) = 0;
    // Set current view orientation from va
    virtual void				SetViewAngles( QAngle& va ) = 0;

    // Retrieve the current game's maxclients setting
    virtual int					GetMaxClients( void ) = 0;

    // Given the string pBinding which may be bound to a key,
    //  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
    virtual	const char			*Key_LookupBinding( const char *pBinding ) = 0;

    // Given the name of the key "mouse1", "e", "tab", etc., return the string it is bound to "+jump", "impulse 50", etc.
    virtual const char			*Key_BindingForKey( ButtonCode_t code ) = 0;

    // Bind a key
    virtual	void				Key_SetBinding( ButtonCode_t code, const char *pBinding ) = 0;

    // key trapping (for binding keys)
    virtual void				StartKeyTrapMode( void ) = 0;
    virtual bool				CheckDoneKeyTrapping( ButtonCode_t &code ) = 0;

    // Returns true if the player is fully connected and active in game (i.e, not still loading)
    virtual bool				IsInGame( void ) = 0;
    // Returns true if the player is connected, but not necessarily active in game (could still be loading)
    virtual bool				IsConnected( void ) = 0;
    // Returns true if the loading plaque should be drawn
    virtual bool				IsDrawingLoadingImage( void ) = 0;
    virtual void				HideLoadingPlaque( void ) = 0;

    // Prints the formatted string to the notification area of the screen ( down the right hand edge
    //  numbered lines starting at position 0
    virtual void				Con_NPrintf( int pos, PRINTF_FORMAT_STRING const char *fmt, ... ) = 0;
    // Similar to Con_NPrintf, but allows specifying custom text color and duration information
    virtual void				Con_NXPrintf( const struct con_nprint_s *info, PRINTF_FORMAT_STRING const char *fmt, ... ) = 0;

    // Is the specified world-space bounding box inside the view frustum?
    virtual int					IsBoxVisible( const Vector& mins, const Vector& maxs ) = 0;

    // Is the specified world-space boudning box in the same PVS cluster as the view origin?
    virtual int					IsBoxInViewCluster( const Vector& mins, const Vector& maxs ) = 0;

    // Returns true if the specified box is outside of the view frustum and should be culled
    virtual bool				CullBox( const Vector& mins, const Vector& maxs ) = 0;

    // Allow the sound system to paint additional data (during lengthy rendering operations) to prevent stuttering sound.
    virtual void				Sound_ExtraUpdate( void ) = 0;
#if defined(_PS3)
    // Allow sound system updates from engine, ensure only done if sv.IsActive() is true
    virtual void				Sound_ServerUpdateSoundsPS3( void ) = 0;
#endif

    // Get the current game directory ( e.g., hl2, tf2, cstrike, hl1 )
    virtual const char			*GetGameDirectory( void ) = 0;

    // Get access to the world to screen transformation matrix
    virtual const VMatrix& 		WorldToScreenMatrix() = 0;

    // Get the matrix to move a point from world space into view space
    // (translate and rotate so the camera is at the origin looking down X).
    virtual const VMatrix& 		WorldToViewMatrix() = 0;

    // The .bsp file can have mod-specified data lumps. These APIs are for working with such game lumps.

    // Get mod-specified lump version id for the specified game data lump
    virtual int					GameLumpVersion( int lumpId ) const = 0;
    // Get the raw size of the specified game data lump.
    virtual int					GameLumpSize( int lumpId ) const = 0;
    // Loads a game lump off disk, writing the data into the buffer pointed to bye pBuffer
    // Returns false if the data can't be read or the destination buffer is too small
    virtual bool				LoadGameLump( int lumpId, void* pBuffer, int size ) = 0;

    // Returns the number of leaves in the level
    virtual int					LevelLeafCount() const = 0;

    // Gets a way to perform spatial queries on the BSP tree
    virtual ISpatialQuery*		GetBSPTreeQuery() = 0;

    // Convert texlight to gamma...
    virtual void		LinearToGamma( float* linear, float* gamma ) = 0;

    // Get the lightstyle value
    virtual float		LightStyleValue( int style ) = 0;

    // Computes light due to dynamic lighting at a point
    // If the normal isn't specified, then it'll return the maximum lighting
    virtual void		ComputeDynamicLighting( const Vector& pt, const Vector* pNormal, Vector& color ) = 0;

    // Returns the color of the ambient light
    virtual void		GetAmbientLightColor( Vector& color ) = 0;

    // Returns the dx support level
    virtual int			GetDXSupportLevel() = 0;

    // GR - returns the HDR support status
    virtual bool        SupportsHDR() = 0;

    // Replace the engine's material system pointer.
    virtual void		Mat_Stub( IMaterialSystem *pMatSys ) = 0;

    // Get the name of the current map
    virtual void GetChapterName( char *pchBuff, int iMaxLength ) = 0;
    virtual char const	*GetLevelName( void ) = 0;
    virtual char const	*GetLevelNameShort( void ) = 0;
    virtual char const	*GetMapGroupName( void ) = 0;
#if !defined( NO_VOICE )
    // Obtain access to the voice tweaking API
    virtual struct IVoiceTweak_s *GetVoiceTweakAPI( void ) = 0;
    virtual void SetVoiceCasterID( uint32 casterID ) = 0;
#endif
    // Tell engine stats gathering system that the rendering frame is beginning/ending
    virtual void		EngineStats_BeginFrame( void ) = 0;
    virtual void		EngineStats_EndFrame( void ) = 0;

    // This tells the engine to fire any events (temp entity messages) that it has queued up this frame.
    // It should only be called once per frame.
    virtual void		FireEvents() = 0;

    // Returns an area index if all the leaves are in the same area. If they span multple areas, then it returns -1.
    virtual int			GetLeavesArea( unsigned short *pLeaves, int nLeaves ) = 0;

    // Returns true if the box touches the specified area's frustum.
    virtual bool		DoesBoxTouchAreaFrustum( const Vector &mins, const Vector &maxs, int iArea ) = 0;
    virtual int			GetFrustumList( Frustum_t **pList, int listMax ) = 0;
    virtual bool		ShouldUseAreaFrustum( int area ) = 0;

    // Sets the hearing origin (i.e., the origin and orientation of the listener so that the sound system can spatialize
    //  sound appropriately ).
    virtual void		SetAudioState( const AudioState_t& state ) = 0;

    // Sentences / sentence groups
    virtual int			SentenceGroupPick( int groupIndex, char *name, int nameBufLen ) = 0;
    virtual int			SentenceGroupPickSequential( int groupIndex, char *name, int nameBufLen, int sentenceIndex, int reset ) = 0;
    virtual int			SentenceIndexFromName( const char *pSentenceName ) = 0;
    virtual const char *SentenceNameFromIndex( int sentenceIndex ) = 0;
    virtual int			SentenceGroupIndexFromName( const char *pGroupName ) = 0;
    virtual const char *SentenceGroupNameFromIndex( int groupIndex ) = 0;
    virtual float		SentenceLength( int sentenceIndex ) = 0;

    // Computes light due to dynamic lighting at a point
    // If the normal isn't specified, then it'll return the maximum lighting
    // If pBoxColors is specified (it's an array of 6), then it'll copy the light contribution at each box side.
    virtual void		ComputeLighting( const Vector& pt, const Vector* pNormal, bool bClamp, Vector& color, Vector *pBoxColors=NULL ) = 0;

    // Activates/deactivates an occluder...
    virtual void		ActivateOccluder( int nOccluderIndex, bool bActive ) = 0;
    virtual bool		IsOccluded( int occlusionViewId, const Vector &vecAbsMins, const Vector &vecAbsMaxs ) = 0;
    virtual int			GetOcclusionViewId() const = 0;

    // The save restore system allocates memory from a shared memory pool, use this allocator to allocate/free saverestore
    //  memory.
    virtual void		*SaveAllocMemory( size_t num, size_t size ) = 0;
    virtual void		SaveFreeMemory( void *pSaveMem ) = 0;

    // returns info interface for client netchannel
    virtual INetChannelInfo	*GetNetChannelInfo( void ) = 0;

    // Debugging functionality:
    // Very slow routine to draw a physics model
    virtual void		DebugDrawPhysCollide( const CPhysCollide *pCollide, IMaterial *pMaterial, const matrix3x4_t& transform, const color32 &color )
= 0;
    // This can be used to notify test scripts that we're at a particular spot in the code.
    virtual void		CheckPoint( const char *pName ) = 0;
    // Draw portals if r_DrawPortals is set (Debugging only)
    virtual void		DrawPortals() = 0;
    // Determine whether the client is playing back or recording a demo
    virtual bool		IsPlayingDemo( void ) = 0;
    virtual bool		IsRecordingDemo( void ) = 0;
    virtual bool		IsPlayingTimeDemo( void ) = 0;
    virtual int			GetDemoRecordingTick( void ) = 0;
    virtual int			GetDemoPlaybackTick( void ) = 0;
    virtual int			GetDemoPlaybackStartTick( void ) = 0;
    virtual float		GetDemoPlaybackTimeScale( void ) = 0;
    virtual int			GetDemoPlaybackTotalTicks( void ) = 0;
    // Is the game paused?
    virtual bool		IsPaused( void ) = 0;

    // What is the game timescale multiplied with the host_timescale?
    virtual float GetTimescale( void ) const = 0;

    // Is the game currently taking a screenshot?
    virtual bool		IsTakingScreenshot( void ) = 0;
    // Is this a HLTV broadcast ?
    virtual bool		IsHLTV( void ) = 0;

#if defined( REPLAY_ENABLED )
    // Is this a Replay demo?
    virtual bool		IsReplay( void ) = 0;
    // Download a replay from the given URL
    virtual void		DownloadReplay( int nReplayDownloadGroupId ) = 0;
    // Is replay enabled?
    virtual bool		IsReplayEnabled() = 0;
    // Is replay recording?
    virtual bool		IsReplayRecording() = 0;
    // Get the replay recording tick from server
    virtual int			GetReplayRecordingTick() = 0;
#endif  // REPLAY_ENABLED

    // is this level loaded as just the background to the main menu? (active, but unplayable)
    virtual bool		IsLevelMainMenuBackground( void ) = 0;
    // returns the name of the background level
    virtual void		GetMainMenuBackgroundName( char *dest, int destlen ) = 0;

    // Occlusion system control
    virtual void		SetOcclusionParameters( const OcclusionParams_t &params ) = 0;

    // What language is the user expecting to hear .wavs in, "english" or another...
    virtual void		GetUILanguage( char *dest, int destlen ) = 0;

    // Can skybox be seen from a particular point?
    virtual SkyboxVisibility_t IsSkyboxVisibleFromPoint( const Vector &vecPoint ) = 0;

    // Get the pristine map entity lump string.  (e.g., used by CS to reload the map entities when restarting a round.)
    virtual const char*	GetMapEntitiesString() = 0;

    // Is the engine in map edit mode ?
    virtual bool		IsInEditMode( void ) = 0;

    // current screen aspect ratio (eg. 4.0f/3.0f, 16.0f/9.0f)
    virtual float		GetScreenAspectRatio( int viewportWidth, int viewportHeight ) = 0;

    // allow the game UI to login a user
    virtual bool		REMOVED_SteamRefreshLogin( const char *password, bool isSecure ) = 0;
    virtual bool		REMOVED_SteamProcessCall( bool & finished ) = 0;

    // allow other modules to know about engine versioning (one use is a proxy for network compatability)
    virtual unsigned int	GetEngineBuildNumber() = 0; // engines build
    virtual const char *	GetProductVersionString() = 0; // mods version number (steam.inf)

    // Communicates to the color correction editor that it's time to grab the pre-color corrected frame
    // Passes in the actual size of the viewport
    virtual void			GrabPreColorCorrectedFrame( int x, int y, int width, int height ) = 0;

    virtual bool			IsHammerRunning( ) const = 0;

    // Inserts szCmdString into the command buffer as if it was typed by the client to his/her console.
    // And then executes the command string immediately (vs ClientCmd() which executes in the next frame)
    //
    // Note: this is NOT checked against the FCVAR_CLIENTCMD_CAN_EXECUTE vars.
    virtual void			ExecuteClientCmd( const char *szCmdString ) = 0;

    // returns if the loaded map was processed with HDR info. This will be set regardless
    // of what HDR mode the player is in.
    virtual bool MapHasHDRLighting(void) = 0;
    virtual bool MapHasLightMapAlphaData(void) = 0;

    virtual int	GetAppID() = 0;

    // Just get the leaf ambient light - no caching, no samples
    virtual Vector			GetLightForPointFast(const Vector &pos, bool bClamp) = 0;

    // This version does NOT check against FCVAR_CLIENTCMD_CAN_EXECUTE.
    virtual void			ClientCmd_Unrestricted( const char *szCmdString , bool fromConsoleOrKeybind = false ) = 0;
    // Version that takes userSlot and can ignore checking if the slot validity has been set; required for joystick initialization for splitscreen
    virtual void			ClientCmd_Unrestricted( const char *szCmdString , bool fromConsoleOrKeybind, int nUserSlot, bool bCheckValidSlot = true )
= 0;

    // This used to be accessible through the cl_restrict_server_commands cvar.
    // By default, Valve games restrict the server to only being able to execute commands marked with FCVAR_SERVER_CAN_EXECUTE.
    // By default, mods are allowed to execute any server commands, and they can restrict the server's ability to execute client
    // commands with this function.
    virtual void			SetRestrictServerCommands( bool bRestrict ) = 0;

    // If set to true (defaults to true for Valve games and false for others), then IVEngineClient::ClientCmd
    // can only execute things marked with FCVAR_CLIENTCMD_CAN_EXECUTE.
    virtual void			SetRestrictClientCommands( bool bRestrict ) = 0;

    // Sets the client renderable for an overlay's material proxy to bind to
    virtual void			SetOverlayBindProxy( int iOverlayID, void *pBindProxy ) = 0;

    virtual bool			CopyFrameBufferToMaterial( const char *pMaterialName ) = 0;

    // Causes the engine to read in the user's configuration on disk
    virtual void			ReadConfiguration( const int iController, const bool readDefault ) = 0;

    virtual void SetAchievementMgr( IAchievementMgr *pAchievementMgr ) = 0;
    virtual IAchievementMgr *GetAchievementMgr() = 0;

    virtual bool			MapLoadFailed( void ) = 0;
    virtual void			SetMapLoadFailed( bool bState ) = 0;

    virtual bool			IsLowViolence() = 0;
    virtual const char		*GetMostRecentSaveGame( bool bEnsureExists = false ) = 0;
    virtual void			SetMostRecentSaveGame( const char *lpszFilename ) = 0;

    virtual void			StartXboxExitingProcess() = 0;

    virtual bool			IsSaveInProgress() = 0;
    virtual bool			IsAutoSaveDangerousInProgress() = 0;

    virtual uint			OnStorageDeviceAttached( int iController ) = 0;
    virtual void			OnStorageDeviceDetached( int iController ) = 0;

    virtual const char *	GetSaveDirName() = 0; // get a pointer to the path where saves should go (with a trailing slash already added)

    // generic screenshot writing
    virtual void			WriteScreenshot( const char *pFilename ) = 0;

    virtual void			ResetDemoInterpolation( void ) = 0;

// For non-split screen games this will always be zero
    virtual int				GetActiveSplitScreenPlayerSlot() = 0;
    virtual int				SetActiveSplitScreenPlayerSlot( int slot ) = 0;

    // This is the current # of players on the local host
    virtual bool			SetLocalPlayerIsResolvable( char const *pchContext, int nLine, bool bResolvable ) = 0;
    virtual bool			IsLocalPlayerResolvable() = 0;

    virtual int				GetSplitScreenPlayer( int nSlot ) = 0;
    virtual bool			IsSplitScreenActive() = 0;
    virtual bool			IsValidSplitScreenSlot( int nSlot ) = 0;
    virtual int				FirstValidSplitScreenSlot() = 0; // -1 == invalid
    virtual int				NextValidSplitScreenSlot( int nPreviousSlot ) = 0; // -1 == invalid

    //Finds or Creates a shared memory space, the returned pointer will automatically be AddRef()ed
    virtual ISPSharedMemory *GetSinglePlayerSharedMemorySpace( const char *szName, int ent_num = MAX_EDICTS ) = 0;

    // Computes an ambient cube that includes ALL dynamic lights
    virtual void ComputeLightingCube( const Vector& pt, bool bClamp, Vector *pBoxColors ) = 0;

    //All callbacks have to be registered before demo recording begins. TODO: Macro'ize a way to do it at startup
    virtual void RegisterDemoCustomDataCallback( string_t szCallbackSaveID, pfnDemoCustomDataCallback pCallback ) = 0;
    virtual void RecordDemoCustomData( pfnDemoCustomDataCallback pCallback, const void *pData, size_t iDataLength ) = 0;

    // global sound pitch scaling
    virtual void SetPitchScale( float flPitchScale ) = 0;
    virtual float GetPitchScale( void ) = 0;

    // Load/unload the SFM - used by Replay
    virtual bool		LoadFilmmaker() = 0;
    virtual void		UnloadFilmmaker() = 0;

    // leaf flag management. Allows fast leaf enumeration of leaves that have a flag set

    // set a bit in a leaf flag
    virtual void SetLeafFlag( int nLeafIndex, int nFlagBits ) = 0;

    // you must call this once done modifying flags. Not super fast.
    virtual void RecalculateBSPLeafFlags( void ) = 0;

    virtual bool DSPGetCurrentDASRoomNew(void) = 0;
    virtual bool DSPGetCurrentDASRoomChanged(void) = 0;
    virtual bool DSPGetCurrentDASRoomSkyAbove(void) = 0;
    virtual float DSPGetCurrentDASRoomSkyPercent(void) = 0;
    virtual void SetMixGroupOfCurrentMixer( const char *szgroupname, const char *szparam, float val, int setMixerType) = 0;
    virtual int GetMixLayerIndex( const char *szmixlayername ) = 0;
    virtual void SetMixLayerLevel(int index, float level ) = 0;
    virtual int GetMixGroupIndex( const char *pMixGroupName ) = 0;
    virtual void SetMixLayerTriggerFactor( int nMixLayerIndex, int nMixGroupIndex, float flFactor ) = 0;
    virtual void SetMixLayerTriggerFactor( const char *pMixLayerIndex, const char *pMixGroupIndex, float flFactor ) = 0;

    virtual bool IsCreatingReslist() = 0;
    virtual bool IsCreatingXboxReslist() = 0;

    virtual void SetTimescale( float flTimescale ) = 0;

    // Methods to set/get a gamestats data container so client & server running in same process can send combined data
    virtual void SetGamestatsData( CGamestatsData *pGamestatsData ) = 0;
    virtual CGamestatsData *GetGamestatsData() = 0;

#if defined( USE_SDL ) || defined( OSX )
    // we need to pull delta's from the cocoa mgr, the engine vectors this for us
    virtual void GetMouseDelta( int &x, int &y, bool bIgnoreNextMouseDelta = false ) = 0;
#endif

    // Given the string pBinding which may be bound to a key,
    //  returns the string name of the key to which this string is bound. Returns NULL if no such binding exists
    // Increment start count to iterate through multiple keys bound to the same binding
    // iAllowJoystick defaults to -1 witch returns joystick and non-joystick binds, 0 returns only non-joystick, 1 returns only joystick
    virtual	const char *Key_LookupBindingEx( const char *pBinding, int iUserId = -1, int iStartCount = 0, BindingLookupOption_t nFlags =
BINDINGLOOKUP_ALL ) = 0;

    // returns key_code for specified binding
    virtual int	Key_CodeForBinding( const char *pBinding, int iUserId = -1, int iStartCount = 0, BindingLookupOption_t nFlags = BINDINGLOOKUP_ALL ) =
0;

    // Updates dynamic light state. Necessary for light cache to work properly for d- and elights
    virtual void UpdateDAndELights( void ) = 0;

    // Methods to get bug count for internal dev work stat tracking.
    // Will get the bug count and clear it every map transition
    virtual int			GetBugSubmissionCount() const = 0;
    virtual void		ClearBugSubmissionCount() = 0;

    // Is there water anywhere in the level?
    virtual bool	DoesLevelContainWater() const = 0;

    // How much time was spent in server simulation?
    virtual float	GetServerSimulationFrameTime() const = 0;

    virtual void SolidMoved( class IClientEntity *pSolidEnt, class ICollideable *pSolidCollide, const Vector* pPrevAbsOrigin, bool
accurateBboxTriggerChecks ) = 0; virtual void TriggerMoved( class IClientEntity *pTriggerEnt, bool accurateBboxTriggerChecks ) = 0;

    // Using area bits, check whether the area of the specified point flows into the other areas
    virtual void ComputeLeavesConnected( const Vector &vecOrigin, int nCount, const int *pLeafIndices, bool *pIsConnected ) = 0;

    // Is the engine in Commentary mode?
    virtual bool IsInCommentaryMode( void ) = 0;

    virtual void SetBlurFade( float amount ) = 0;
    virtual bool IsTransitioningToLoad() = 0;

    virtual void SearchPathsChangedAfterInstall() = 0;

    virtual void ConfigureSystemLevel( int nCPULevel, int nGPULevel ) = 0;

    virtual void SetConnectionPassword( char const *pchCurrentPW ) = 0;

    virtual CSteamAPIContext* GetSteamAPIContext() = 0;

    virtual void SubmitStatRecord( char const *szMapName, uint uiBlobVersion, uint uiBlobSize, const void *pvBlob ) = 0;

    // Sends a key values server command, not allowed from scripts execution
    // Params:
    //	pKeyValues	- key values to be serialized and sent to server
    //				  the pointer is deleted inside the function: pKeyValues->deleteThis()
    virtual void ServerCmdKeyValues( KeyValues *pKeyValues ) = 0;
    virtual void SendMessageToServer( INetMessage *pMessage, bool bForceReliable = false, bool bVoice = false ) = 0;
    // Tells the engine what and where to paint
    virtual bool SpherePaintSurface( const model_t *pModel, const Vector& vPosition, BYTE color, float flSphereRadius, float flPaintCoatPercent ) = 0;
    virtual bool HasPaintmap() = 0;
    // Enable paint in the engine for project Paint
    virtual void EnablePaintmapRender() = 0;
    virtual void SphereTracePaintSurface( const model_t *pModel, const Vector& vPosition, const Vector& vContactNormal, float flSphereRadius,
CUtlVector<BYTE>& surfColors ) = 0; virtual void RemoveAllPaint() = 0; virtual void PaintAllSurfaces( BYTE color ) = 0; virtual void RemovePaint(
const model_t *pModel ) = 0;

    virtual bool IsActiveApp() = 0;

    // is this client running inside the same process as an active server?
    virtual bool IsClientLocalToActiveServer() = 0;

    // Callback for LevelInit to tick the progress bar during time consuming operations
    virtual void TickProgressBar() = 0;

    // Returns the requested input context
    virtual InputContextHandle_t GetInputContext( EngineInputContextId_t id ) = 0;

    virtual void GetStartupImage( char *pOutBuff, int nOutBuffSize ) = 0;

    // For the rare case when the client DLL needs to do something different if network backdoor is on.
    virtual bool IsUsingLocalNetworkBackdoor() = 0;

    virtual bool SaveGame( const char *pSaveFilename, bool bIsXSave, char *pOutName, int nOutNameSize, char *pOutComment, int nOutCommentSize ) = 0;

    // Request 'generic' memory stats (returns a list of N named values; caller should assume this list will change over time)
    virtual int GetGenericMemoryStats( GenericMemoryStat_t **ppMemoryStats ) = 0;

    // On exit from a map, this becomes true once all map-related assets are flushed from memory:
    virtual bool GameHasShutdownAndFlushedMemory() = 0;

    //get the command_number from the most recent command the server acknowledged processing
    virtual int GetLastAcknowledgedCommand( void ) = 0;

    virtual void FinishContainerWrites( int iController ) = 0;

    virtual void FinishAsyncSave() = 0;

    virtual int GetServerTick( void ) = 0;

    // return the final directory in the game dir (i.e "cstrike", "hl2", rather than c:\blah\cstrike )
    virtual const char *GetModDirectory( void ) = 0;

    virtual void AudioLanguageChanged() = 0;

    virtual bool IsAutoSaveInProgress() = 0;

    virtual void StartLoadingScreenForCommand( const char* command ) = 0;

    virtual void StartLoadingScreenForKeyValues( KeyValues* keyValues ) = 0;

    // Sos opvars
    virtual bool SOSSetOpvarFloat( const char *pOpVarName, float flValue ) = 0;
    virtual bool SOSGetOpvarFloat( const char *pOpVarName, float &flValue ) = 0;

#if defined(_PS3)
        virtual void* GetHostStateWorldBrush( void )	= 0;
    virtual bool PS3_IsUserRestrictedFromChat( void ) = 0;
    virtual bool PS3_IsUserRestrictedFromOnline( void ) = 0;
    virtual bool PS3_PendingInvitesFound( void ) = 0;
    virtual void PS3_ShowInviteOverlay( void ) = 0;

    virtual bool  bOverrideCSMConvars( void )		= 0;
    virtual bool  bDrawWorldIntoCSM( void )			= 0;
    virtual bool  bDrawStaticPropsIntoCSM( void )	= 0;
    virtual float GetCSMMaxDist( void )				= 0;
#endif

    virtual bool IsSubscribedMap( const char *pchMapName, bool bOnlyOnDisk ) = 0;
    virtual bool IsFeaturedMap( const char *pchMapName, bool bOnlyOnDisk ) = 0;

    // Access demo playback parameters
    virtual CDemoPlaybackParameters_t const * GetDemoPlaybackParameters() = 0;

    // Client version from the steam.inf, this will be compared to the GC version
    virtual int GetClientVersion() const = 0; // engines build

    virtual bool IsDemoSkipping() = 0;
    virtual void SetDemoImportantEventData( const KeyValues *pData ) = 0;
    // clear any temp entity events that are stacked up
    virtual void ClearEvents() = 0;

    virtual float GetSafeZoneXMin( void ) const = 0;

    virtual bool IsVoiceRecording() const = 0;
    virtual void ForceVoiceRecordOn() const = 0;

    virtual int GetConnectionDataProtocol() const = 0;

    virtual bool EngineGotvSyncPacket( const CEngineGotvSyncPacket *pPkt ) = 0;

    virtual const char* AliasToCommandString( const char* szAliasName ) = 0;
};
*/
