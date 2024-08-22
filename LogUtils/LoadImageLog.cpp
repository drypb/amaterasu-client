#include "../mainHeader.h"
#include "../LogUtils.h"

/**
 * LogLoadImage - Log image load information
 * @LoadImageInfo: LOAD_IMAGE_INFO struct containing image load details
 * @logFile: FILE pointer to the log file
 *
 * Writes image load information to the log file.
 */
void LogLoadImage(LOAD_IMAGE_INFO LoadImageInfo, FILE* logFile)
{
    fprintf(logFile, "\"pid\": \"%llu\",\n", (ULONGLONG)LoadImageInfo.PID);
    fprintf(logFile, "\"full image name\": \"%ws\"", LoadImageInfo.FullImageName);

    if (LoadImageInfo.ImageInfo.ExtendedInfoPresent) {
        fprintf(logFile, ",\n\"file name\": \"%ws\"\n", LoadImageInfo.FileName);
    }
    else {
        fprintf(logFile, "\n");
    }
}
