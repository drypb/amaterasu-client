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
    log(logFile, "pid", (ULONGLONG)LoadImageInfo.PID);
    log(logFile, "full_image_name", (ULONGLONG)LoadImageInfo.FullImageName);

    if (LoadImageInfo.ImageInfo.ExtendedInfoPresent) {
        log(logFile, "file_name", LoadImageInfo.FileName);
    }
    else {
        fprintf(logFile, "\n");
    }
}
