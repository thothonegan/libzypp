ADD_SUBDIRECTORY(base)

# set the vendor.d paths correctly for the tests
SET(VENDOR_D "${LIBZYPP_SOURCE_DIR}/tests/zypp/data/Vendor/vendors.d")
FILE(MAKE_DIRECTORY "${LIBZYPP_BINARY_DIR}/tests/zypp/data/Vendor")
CONFIGURE_FILE(${LIBZYPP_SOURCE_DIR}/tests/zypp/data/Vendor/zypp2.conf.cmake ${LIBZYPP_BINARY_DIR}/tests/zypp/data/Vendor/zypp2.conf @ONLY)

ADD_TESTS(
  Arch
  Capabilities
  CheckSum
  ContentType
  CpeId
  Date
  DrunkenBishop
  Dup
  Digest
  Deltarpm
  Edition
  ExtendedPool
  Fetcher
  FileChecker
  Flags
  InstanceId
  KeyRing
  Locale
  Locks
  MediaSetAccess
  PathInfo
  Pathname
  PluginFrame
  PoolQueryCC
  PoolQuery
  ProgressData
  PtrTypes
  PublicKey
  RWPtr
  RepoInfo
  RepoManager
  RepoStatus
  ResKind
  Resolver
  ResStatus
  Selectable
  SetRelationMixin
  SetTracker
  StrMatcher
  Target
  Url
  UserData
  Vendor
  Vendor2
)

