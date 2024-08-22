#include "../mainHeader.h"

#define isEnabled(a) (a & SE_PRIVILEGE_ENABLED) == SE_PRIVILEGE_ENABLED
/**
 * LogTokenType - Log token type
 * @Type: TOKEN_TYPE enum containing the token type
 * @logFile: FILE pointer to the log file
 *
 * Logs the type of token (primary or impersonation).
 */
static inline void LogTokenType(TOKEN_TYPE Type, FILE* logFile)
{
    fprintf(logFile, "\"token type\": ");
    switch (Type) {
    case TokenPrimary:
        fprintf(logFile, "\"primary token\"");
        break;
    case TokenImpersonation:
        fprintf(logFile, "\"impersonation token\"");
        break;
    default:
        fprintf(logFile, "\"undefined token type %d\"", Type);
        break;
    }
    fprintf(logFile, ",\n");
}

/**
 * GetPrivilegeNameSize - Get the size of a privilege name
 * @Privilege: LUID_AND_ATTRIBUTES struct containing privilege details
 *
 * Returns the size of the privilege name.
 */
static inline ULONG GetPrivilegeNameSize(LUID_AND_ATTRIBUTES Privilege)
{
    ULONG Size = 0;
    LookupPrivilegeName(NULL, &Privilege.Luid, NULL, &Size);
    return Size;
}

/**
 * LogPrivilegeName - Log privilege name and status
 * @Privilege: LUID_AND_ATTRIBUTES struct containing privilege details
 * @logFile: FILE pointer to the log file
 *
 * Logs the name and status (enabled or disabled) of a privilege.
 */
static inline void LogPrivilegeName(LUID_AND_ATTRIBUTES Privilege, FILE* logFile)
{
    ULONG NameSize = GetPrivilegeNameSize(Privilege) + 1;
    LPWSTR Name = (LPWSTR)malloc(sizeof(WCHAR) * NameSize);

    LookupPrivilegeName(NULL, &Privilege.Luid, Name, &NameSize);

    fprintf(logFile, "\"%ws\": \"%s\"", Name, isEnabled(Privilege.Attributes) ? "Enabled" : "Disabled");

    free(Name);
}

/**
 * LogPrivileges - Log privileges
 * @Privileges: PRIVILEGES struct containing privileges details
 * @logFile: FILE pointer to the log file
 *
 * Logs a list of privileges associated with a token.
 */
static inline void LogPrivileges(PRIVILEGES Privileges, FILE* logFile)
{
    fprintf(logFile, "\"privileges\": [\n");

    for (ULONG i = 0; i < Privileges.PrivilegeCount; i++) {
        fprintf(logFile, "  { ");
        LogPrivilegeName(Privileges.Privileges[i], logFile);
        fprintf(logFile, " }");
        if (i < Privileges.PrivilegeCount - 1) {
            fprintf(logFile, ",\n");
        }
    }

    fprintf(logFile, "\n],\n");
}

/**
 * LogSecurityImpersonationLevel - Log security impersonation level
 * @ImpersonationLevel: SECURITY_IMPERSONATION_LEVEL enum containing impersonation level details
 * @logFile: FILE pointer to the log file
 *
 * Logs the level of impersonation (anonymous, identification, impersonation, delegation).
 */
static inline void LogSecurityImpersonationLevel(SECURITY_IMPERSONATION_LEVEL ImpersonationLevel, FILE* logFile)
{
    fprintf(logFile, "\"impersonation level\": ");
    switch (ImpersonationLevel) {
    case SecurityAnonymous:
        fprintf(logFile, "\"SecurityAnonymous\"");
        break;
    case SecurityIdentification:
        fprintf(logFile, "\"SecurityIdentification\"");
        break;
    case SecurityImpersonation:
        fprintf(logFile, "\"SecurityImpersonation\"");
        break;
    case SecurityDelegation:
        fprintf(logFile, "\"SecurityDelegation\"");
        break;
    }
    fprintf(logFile, ",\n");
}

/**
 * LogTokenInfo - Log token information
 * @TokenInfo: TOKEN_INFO struct containing token details
 * @logFile: FILE pointer to the log file
 *
 * Logs detailed information about a token, including type, privileges, and impersonation level.
 */
void LogTokenInfo(TOKEN_INFO TokenInfo, FILE* logFile)
{
    LogTokenType(TokenInfo.Type, logFile);
    LogPrivileges(TokenInfo.Privileges, logFile);

    fprintf(logFile, "\"elevation status\": \"%d\",\n", TokenInfo.TokenElevation.TokenIsElevated);

    if (TokenInfo.Type == TokenImpersonation) {
        LogSecurityImpersonationLevel(TokenInfo.ImpersonationLevel, logFile);
    }
}
