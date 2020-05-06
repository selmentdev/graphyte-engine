
// begin: fileapi.h
#undef CreateDirectory
#undef CreateFile
#undef DefineDosDevice
#undef DeleteFile
#undef DeleteVolumeMountPoint
#undef FindFirstChangeNotification
#undef FindFirstFile
#undef FindFirstFileEx
#undef FindFirstVolume
#undef FindNextFile
#undef FindNextVolume
#undef GetDiskFreeSpace
#undef GetDiskFreeSpaceEx
#undef GetDriveType
#undef GetFileAttributes
#undef GetFileAttributesEx
#undef GetFinalPathNameByHandle
#undef GetFullPathName
#undef GetLogicalDriveStrings
#undef GetLongPathName
#undef GetShortPathName
#undef GetTempFileName
#undef GetVolumeInformation
#undef GetVolumePathName
#undef QueryDosDevice
#undef RemoveDirectory
#undef SetFileAttributes
#undef GetTempPath
#undef GetVolumeNameForVolumeMountPoint
#undef GetVolumePathNamesForVolumeName
#undef GetCompressedFileSize
// end: fileapi.h

// begin: winnt.h
// #undef MemoryBarrier -- this one is actually preety neat
#undef YieldProcessor
// end: winnt.h

// begin: WinBase.h
#undef Yield
#undef GetBinaryType
#undef GetLongPathNameTransacted
#undef SetFileShortName
#undef FormatMessage
#undef CreateMailslot
#undef EncryptFile
#undef DecryptFile
#undef FileEncryptionStatus
#undef OpenEncryptedFileRaw
#undef CreateSemaphore
#undef CreateWaitableTimer
#undef CreateFileMapping
#undef CreateFileMappingNuma
#undef OpenFileMapping
#undef LoadLibrary
#undef QueryFullProcessImageName
#undef FatalAppExit
#undef GetStartupInfo
#undef GetFirmwareEnvironmentVariable
#undef GetFirmwareEnvironmentVariableEx
#undef SetFirmwareEnvironmentVariable
#undef SetFirmwareEnvironmentVariableEx
#undef FindResource
#undef FindResourceEx
#undef EnumResourceTypes
#undef EnumResourceNames
#undef EnumResourceLanguages
#undef BeginUpdateResource
#undef UpdateResource
#undef EndUpdateResource
#undef GlobalAddAtom
#undef GlobalAddAtomEx
#undef GlobalFindAtom
#undef GlobalGetAtomName
#undef AddAtom
#undef FindAtom
#undef GetAtomName
#undef GetProfileInt
#undef GetProfileString
#undef WriteProfileString
#undef GetProfileSection
#undef WriteProfileSection
#undef GetPrivateProfileInt
#undef GetPrivateProfileString
#undef WritePrivateProfileString
#undef GetPrivateProfileSection
#undef WritePrivateProfileSection
#undef GetPrivateProfileSectionNames
#undef GetPrivateProfileStruct
#undef WritePrivateProfileStruct
#undef GetSystemWow64Directory
#undef SetDllDirectory
#undef GetDllDirectory
#undef CreateDirectoryEx
#undef CreateDirectoryTransacted
#undef RemoveDirectoryTransacted
#undef GetFullPathNameTransacted
#undef CreateFileTransacted
#undef SetFileAttributesTransacted
#undef GetFileAttributesTransacted
#undef GetCompressedFileSizeTransacted
#undef DeleteFileTransacted
#undef CheckNameLegalDOS8Dot3
#undef FindFirstFileTransacted
#undef CopyFile
#undef CopyFileEx
#undef CopyFileTransacted
#undef MoveFile
#undef MoveFileEx
#undef MoveFileWithProgress
#undef MoveFileTransacted
#undef ReplaceFile
#undef CreateHardLink
#undef CreateHardLinkTransacted
#undef CreateNamedPipe
#undef GetNamedPipeHandleState
#undef CallNamedPipe
#undef WaitNamedPipe
#undef GetNamedPipeClientComputerName
#undef SetVolumeLabel
#undef ClearEventLog
#undef BackupEventLog
#undef OpenEventLog
#undef RegisterEventSource
#undef OpenBackupEventLog
#undef ReadEventLog
#undef ReportEvent
#undef AccessCheckAndAuditAlarm
#undef AccessCheckByTypeAndAuditAlarm
#undef AccessCheckByTypeResultListAndAuditAlarm
#undef AccessCheckByTypeResultListAndAuditAlarmByHandle
#undef ObjectOpenAuditAlarm
#undef ObjectPrivilegeAuditAlarm
#undef ObjectCloseAuditAlarm
#undef ObjectDeleteAuditAlarm
#undef PrivilegedServiceAuditAlarm
#undef GetFileSecurity
#undef IsBadStringPtr
#undef LookupAccountSid
#undef LookupAccountName
#undef LookupAccountNameLocal
#undef LookupAccountSidLocal
#undef LookupPrivilegeValue
#undef LookupPrivilegeName
#undef LookupPrivilegeDisplayName
#undef BuildCommDCB
#undef BuildCommDCBAndTimeouts
#undef CommConfigDialog
#undef GetDefaultCommConfig
#undef SetDefaultCommConfig
#undef GetComputerName
#undef SetComputerName
#undef DnsHostnameToComputerName
#undef GetUserName
#undef LogonUser
#undef LogonUserEx
#undef CreateProcessAsUser
#undef CreatePrivateNamespace
#undef OpenPrivateNamespace
#undef CreateBoundaryDescriptor
#undef GetCurrentHwProfile
#undef VerifyVersionInfo
#undef CreateJobObject
#undef OpenJobObject
#undef FindFirstVolumeMountPoint
#undef FindNextVolumeMountPoint
#undef SetVolumeMountPoint
#undef CreateActCtx
#undef FindActCtxSectionString
#undef CreateSymbolicLink
#undef CreateSymbolicLinkTransacted
// end: WinBase.h

// begin: WinUser.h
#undef LoadKeyboardLayout
#undef GetKeyboardLayoutName
#undef CreateDesktop
#undef CreateDesktopEx
#undef OpenDesktop
#undef EnumDesktops
#undef CreateWindowStation
#undef OpenWindowStation
#undef EnumWindowStations
#undef GetUserObjectInformation
#undef SetUserObjectInformation
#undef RegisterWindowMessage
#undef GetMessage
#undef DispatchMessage
#undef PeekMessage
#undef SendMessage
#undef SendMessageTimeout
#undef SendNotifyMessage
#undef SendMessageCallback
#undef BroadcastSystemMessageEx
#undef BroadcastSystemMessage
#undef RegisterDeviceNotification
#undef PostMessage
#undef PostThreadMessage
#undef PostAppMessage
#undef DefWindowProc
#undef CallWindowProc
#undef CallWindowProc
#undef RegisterClass
#undef UnregisterClass
#undef GetClassInfo
#undef RegisterClassEx
#undef GetClassInfoEx
#undef CreateWindowEx
#undef CreateWindow
#undef CreateDialogParam
#undef CreateDialogIndirectParam
#undef CreateDialog
#undef CreateDialogIndirect
#undef DialogBoxParam
#undef DialogBoxIndirectParam
#undef DialogBox
#undef DialogBoxIndirect
#undef SetDlgItemText
#undef GetDlgItemText
#undef SendDlgItemMessage
#undef DefDlgProc
#undef CallMsgFilter
#undef RegisterClipboardFormat
#undef GetClipboardFormatName
#undef CharToOem
#undef OemToChar
#undef CharToOemBuff
#undef OemToCharBuff
#undef CharUpper
#undef CharUpperBuff
#undef CharLower
#undef CharLowerBuff
#undef CharNext
#undef CharPrev
#undef IsCharAlpha
#undef IsCharAlphaNumeric
#undef IsCharUpper
#undef IsCharLower
#undef GetKeyNameText
#undef VkKeyScan
#undef VkKeyScanEx
#undef MapVirtualKey
#undef MapVirtualKeyEx
#undef LoadAccelerators
#undef CreateAcceleratorTable
#undef CopyAcceleratorTable
#undef TranslateAccelerator
#undef LoadMenu
#undef LoadMenuIndirect
#undef ChangeMenu
#undef GetMenuString
#undef InsertMenu
#undef AppendMenu
#undef ModifyMenu
#undef InsertMenuItem
#undef GetMenuItemInfo
#undef SetMenuItemInfo
#undef DrawText
#undef DrawTextEx
#undef GrayString
#undef DrawState
#undef TabbedTextOut
#undef GetTabbedTextExtent
#undef SetProp
#undef GetProp
#undef RemoveProp
#undef EnumPropsEx
#undef EnumProps
#undef SetWindowText
#undef GetWindowText
#undef GetWindowTextLength
#undef MessageBox
#undef MessageBoxEx
#undef MessageBoxIndirect
#undef GetWindowLong
#undef SetWindowLong
#undef GetWindowLongPtr
#undef SetWindowLongPtr
#undef GetClassLong
#undef SetClassLong
#undef GetClassLongPtr
#undef SetClassLongPtr
#undef FindWindow
#undef FindWindowEx
#undef GetClassName
#undef SetWindowsHook
#undef SetWindowsHookEx
#undef LoadBitmap
#undef LoadCursor
#undef LoadCursorFromFile
#undef LoadIcon
#undef PrivateExtractIcons
#undef LoadImage
#undef GetIconInfoEx
#undef LoadString
#undef IsDialogMessage
#undef DlgDirList
#undef DlgDirSelectEx
#undef DlgDirListComboBox
#undef DlgDirSelectComboBoxEx
#undef DefFrameProc
#undef DefMDIChildProc
#undef CreateMDIWindow
#undef WinHelp
#undef ChangeDisplaySettings
#undef ChangeDisplaySettingsEx
#undef EnumDisplaySettings
#undef EnumDisplaySettingsEx
#undef EnumDisplayDevices
#undef SystemParametersInfo
#undef GetMonitorInfo
#undef GetWindowModuleFileName
#undef GetAltTabInfo
#undef GetRawInputDeviceInfo
// end: WinUser.h

// begin: processenv.h
#undef GetEnvironmentStrings
#undef SetEnvironmentStrings
#undef FreeEnvironmentStrings
#undef GetCommandLine
#undef GetEnvironmentVariable
#undef SetEnvironmentVariable
#undef ExpandEnvironmentStrings
#undef SetCurrentDirectory
#undef GetCurrentDirectory
#undef SearchPath
#undef NeedCurrentDirectoryForExePath
// end: processenv.h

// begin: winreg.h
#undef RegConnectRegistry
#undef RegConnectRegistryEx
#undef RegCreateKey
#undef RegCreateKeyEx
#undef RegCreateKeyTransacted
#undef RegDeleteKey
#undef RegDeleteKeyEx
#undef RegDeleteKeyTransacted
#undef RegDeleteValue
#undef RegEnumKey
#undef RegEnumKeyEx
#undef RegEnumValue
#undef RegLoadKey
#undef RegOpenKey
#undef RegOpenKeyEx
#undef RegOpenKeyTransacted
#undef RegQueryInfoKey
#undef RegQueryValue
#undef RegQueryMultipleValues
#undef RegQueryValueEx
#undef RegReplaceKey
#undef RegRestoreKey
#undef RegSaveKey
#undef RegSetValue
#undef RegSetValueEx
#undef RegUnLoadKey
#undef RegDeleteKeyValue
#undef RegSetKeyValue
#undef RegDeleteTree
#undef RegCopyTree
#undef RegGetValue
#undef RegCopyTree
#undef RegLoadMUIString
#undef RegLoadAppKey
#undef InitiateSystemShutdown
#undef AbortSystemShutdown
#undef InitiateSystemShutdownEx
#undef InitiateShutdown
#undef RegSaveKeyEx
// end: winreg.h

// begin: shellapi.h
#undef DragQueryFile
#undef ShellExecute
#undef FindExecutable
#undef ShellAbout
#undef ExtractIconEx
#undef SHFileOperation
#undef ShellExecuteEx
#undef SHQueryRecycleBin
#undef SHEmptyRecycleBin
#undef Shell_NotifyIcon
#undef SHGetFileInfo
#undef SHGetDiskFreeSpaceEx
#undef SHInvokePrinterCommand
#undef ShellMessageBox
#undef IsLFNDrive
#undef SHEnumerateUnreadMailAccounts
#undef SHGetUnreadMailCount
#undef SHSetUnreadMailCount
// end: shellapi.h

// begin: sysinfoapi.h
#undef GetSystemDirectory
#undef GetWindowsDirectory
#undef GetSystemWindowsDirectory
#undef GetComputerNameEx
#undef SetComputerNameEx
#undef GetVersionEx
// end: sysinfoapi.h

// begin: libloaderapi.h
#undef GetModuleFileName
#undef GetModuleHandle
#undef GetModuleHandleEx
#undef LoadLibraryEx
#undef LoadString
#undef EnumResourceLanguagesEx
#undef EnumResourceNamesEx
#undef EnumResourceTypesEx
// end: libloaderapi.h

// begin: synchapi.h
#undef CreateMutex
#undef OpenMutex
#undef CreateEvent
#undef OpenEvent
#undef OpenSemaphore
#undef OpenWaitableTimer
#undef CreateMutexEx
#undef CreateEventEx
#undef CreateSemaphoreEx
#undef CreateWaitableTimerEx
// end: synchapi.h

// begin: winspool.h
#undef SetPort
// end: winspool.h

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif