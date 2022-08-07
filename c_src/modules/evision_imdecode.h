#ifdef HAVE_OPENCV_IMGCODECS

#ifndef EVISION_OPENCV_IMDECODE_H
#define EVISION_OPENCV_IMDECODE_H

// @evision enable_with: imgcodecs

#include <erl_nif.h>
#include "../nif_utils.hpp"

using namespace evision::nif;

// @evision c: imdecode,evision_cv_imdecode,1
// @evision nif: def imdecode(_opts \\ []), do: :erlang.nif_error("imdecode not loaded")
static ERL_NIF_TERM evision_cv_imdecode(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    using namespace cv;
    ERL_NIF_TERM error_term = 0;
    std::map<std::string, ERL_NIF_TERM> erl_terms;
    int nif_opts_index = 0; // <- autogenerated value
    if (nif_opts_index < argc) {
        evision::nif::parse_arg(env, nif_opts_index, argv, erl_terms);
    }

    {
        ERL_NIF_TERM erl_binary = evision_get_kw(env, erl_terms, "buf");
        ErlNifBinary buf;
        int flags;
        if (enif_inspect_binary(env, erl_binary, &buf) &&
            evision_to_safe(env, evision_get_kw(env, erl_terms, "flags"), flags, ArgInfo("flags", 0))) {
            Mat retval;
            int error_flag = false;
            cv::Mat bufMat = cv::Mat(1, buf.size, CV_8UC1, buf.data);
            ERRWRAP2(retval = cv::imdecode(bufMat, flags), env, error_flag, error_term);
            if (!error_flag) {
                return evision::nif::ok(env, evision_from(env, retval));
            }
        }
    }

    if (error_term != 0) return error_term;
    else return evision::nif::error(env, "overload resolution failed");
}

#endif // EVISION_OPENCV_IMDECODE_H

#endif // HAVE_OPENCV_IMGCODECS
