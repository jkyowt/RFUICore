/*!
	Debug output kit(dout)
	RFKit

	ver 1.1.0
 
    Copyright (c) 2012 BB9z
    http://github.com/bb9z/RFKit

    The MIT License (MIT)
    http://www.opensource.org/licenses/mit-license.php
 */

#ifndef _DOUT_H_
#define _DOUT_H_

#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSException.h>

#pragma mark - Config

/** RFDebugLevel
    Use this macro to change dout behave.
 
    5   Info
    4   
    3   Show warning.
    2   Debug, show error. DOUT_LOG_ENABLE on.
    1   Default, DOUT_LOG_ENABLE off. For production environment.
    0   Silent.
 */
#ifndef RFDebugLevel
#   if DEBUG
#       define RFDebugLevel 2
#   else
#       define RFDebugLevel 1
#   endif
#endif

// Auto define DEBUG if RFDebugLevel > 1
#ifndef DEBUG
#   if RFDebugLevel > 1
#       define DEBUG 1
#   endif
#endif

// If DOUT_ASSERT_AT_ERROR is enabled, DOUT_TREAT_ERROR_AS_EXCEPTION will not available.
#ifndef DOUT_ASSERT_AT_ERROR
#   define DOUT_ASSERT_AT_ERROR 0
#endif
#ifndef DOUT_ASSERT_AT_WANRNING
#   define DOUT_ASSERT_AT_WANRNING 0
#endif

#ifndef DOUT_TREAT_ERROR_AS_EXCEPTION
#   define DOUT_TREAT_ERROR_AS_EXCEPTION 0
#endif
#ifndef DOUT_TREAT_WANRNING_AS_EXCEPTION
#   define DOUT_TREAT_WANRNING_AS_EXCEPTION 0
#endif


/** DOUT_LOG_ENABLE
    It controll all debug log output.
 
    Tip: Howto set DOUT_LOG_ENABLE in Build Settings.
	
        Use Preprocessor macros, or Other C Flags.
 
        If you use C flags, set -Dmacro[=defn] to define macro.
        For example, to disable dout, set -DDOUT_LOG_ENABLE=0
 */
#ifndef DOUT_LOG_ENABLE
#   if RFDebugLevel > 1
#       define DOUT_LOG_ENABLE 1
#   else
#       define DOUT_LOG_ENABLE 0
#   endif
#endif

//#define DOUT_FALG_TRACE 1

/** DOUT_FALG_TRACE
	This macro used to help location dout print statements.
 */
#ifndef DOUT_FALG_TRACE
#	define DOUT_FALG_TRACE 0
#endif

/** DOUT_TRACE_FORMATTER
	This macro should define as NSString
 */
#ifndef DOUT_TRACE_FORMATTER
#	if DOUT_FALG_TRACE
#		define DOUT_TRACE_FORMATTER [NSString stringWithFormat:@"%@:%d >> ",[[NSString stringWithUTF8String:__FILE__] lastPathComponent],__LINE__]
#	else
#		define DOUT_TRACE_FORMATTER @""
#	endif
#endif

#pragma mark - Variables log helper
/// main
#if DOUT_LOG_ENABLE
	#define dout(format,...)\
		if(DOUT_LOG_ENABLE) NSLog([DOUT_TRACE_FORMATTER stringByAppendingFormat:format, ##__VA_ARGS__]);

	#define douto(NSObject)\
        dout(@"%s = <%@> %@", #NSObject, [(NSObject) class], NSObject)

    #define doutp(pointer)\
        dout(@"%s -> %p", #pointer, pointer)

	#define dout_bool(boolVar)\
        dout(@"%s = %@", #boolVar, boolVar?@"YES":@"NO")

    #define dout_int(intVar)\
        dout(@"%s = %i", #intVar, (int)intVar)

	#define dout_float(floatVar)\
        dout(@"%s = %f", #floatVar, (float)floatVar)

	#define dout_point(point_struct_with_x_y)\
        dout(@"%s = {%f, %f}", #point_struct_with_x_y, (float)point_struct_with_x_y.x, (float)point_struct_with_x_y.y)

	#define dout_size(size_struct_with_width_height)\
        dout(@"%s = {%f, %f}", #size_struct_with_width_height, (float)size_struct_with_width_height.width, size_struct_with_width_height.height)

	#define dout_rect(CGRect)\
        dout(@"%s = {%f, %f,%f, %f}", #CGRect, CGRect.origin.x, CGRect.origin.y, CGRect.size.width, CGRect.size.height)

	#define douts(NSString)\
        dout(@"%@", NSString)

	#define doutwork()\
        dout(@"%s: It Works!", __FUNCTION__)

	#define douttrace()\
        dout(@"%s @%@", __PRETTY_FUNCTION__, [NSThread callStackSymbols])

#else
	#define dout(...)
	#define douts(...)
	#define douto(...)
    #define doutp(...)
	#define dout_bool(...)
    #define dout_int(...)
	#define dout_float(...)
	#define dout_point(...)
	#define dout_size(...)
	#define dout_rect(...)
	#define doutf(...)
	#define doutwork(...)
	#define douttrace(...)

#endif

#pragma mark Log helper
#ifndef dout_info
    #if RFDebugLevel >= 5
        #define dout_info(format,...) dout(@"<Info> %@", [NSString stringWithFormat:format, ##__VA_ARGS__])
    #else
        #define dout_info(...)
    #endif
#endif

#ifndef dout_warning
    #if RFDebugLevel >= 3
        #if DOUT_ASSERT_AT_ERROR
            #define dout_warning(format, ...)\
                NSAssert(false, format, ##__VA_ARGS__);

        #elif DOUT_TREAT_ERROR_AS_EXCEPTION
            #define dout_warning(format, ...)\
                @throw [NSException exceptionWithName:@"DOUT Warning" reason:[NSString stringWithFormat:format, ##__VA_ARGS__] userInfo:nil];

        #else
            #define dout_warning(format, ...)\
                dout(@"<Warning> %@", [NSString stringWithFormat:format, ##__VA_ARGS__])

        #endif

    #else
        #define dout_warning(...)
    #endif
#endif

#ifndef dout_error
    #if RFDebugLevel >= 2
        #if DOUT_ASSERT_AT_ERROR
            #define dout_error(format, ...)\
                NSAssert(false, format, ##__VA_ARGS__);

        #elif DOUT_TREAT_ERROR_AS_EXCEPTION
            #define dout_error(format, ...)\
                @throw [NSException exceptionWithName:@"DOUT Error" reason:[NSString stringWithFormat:format, ##__VA_ARGS__] userInfo:nil];

        #else
            #define dout_error(format, ...)\
                dout(@"<Error> %@", [NSString stringWithFormat:format, ##__VA_ARGS__]);
        #endif
    #else
        #define dout_error(...)
    #endif
#endif


#pragma mark Segment

#if DOUT_LOG_ENABLE
    #define DOUT_START if(DOUT_LOG_ENABLE){
    #define DOUT_END }

    #define DAUTORELEASEPOOL_START	@autoreleasepool{
    #define DAUTORELEASEPOOL_END	}

    #define DTRYCATCH_START @try {
    #define DTRYCATCH_END \
        } @catch (NSException *exception) { \
            douto(exception) \
            douttrace() \
        } @finally {}

#else
    #define DOUT_START
    #define DOUT_END

    #define DAUTORELEASEPOOL_START
    #define DAUTORELEASEPOOL_END

    #define DTRYCATCH_START
    #define DTRYCATCH_END

#endif

#pragma mark - _dout
/// _dout
#define _dout(...)
#define _douts(...)
#define _douto(...)
#define _doutp(...)
#define _dout_bool(...)
#define _dout_int(...)
#define _dout_float(...)
#define _dout_point(...)
#define _dout_size(...)
#define _dout_rect(...)
#define _doutf(...)
#define _doutwork(...)
#define _douttrace(...)

#define _dout_info(...)
#define _dout_warning(...)
#define _dout_error(...)

void _dout_log_config();

#endif
