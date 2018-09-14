// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_WELL_KNOWN_PARAMETERS_H_
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_WELL_KNOWN_PARAMETERS_H_

#include "google/cloud/internal/optional.h"
#include "google/cloud/storage/version.h"
#include <cstdint>
#include <string>

namespace google {
namespace cloud {
namespace storage {
inline namespace STORAGE_CLIENT_NS {
namespace internal {
/**
 * Defines well-known request headers using the CRTP.
 *
 * @tparam P the type we will use to represent the query parameter.
 * @tparam T the C++ type of the query parameter
 */
template <typename P, typename T>
class WellKnownParameter {
 public:
  WellKnownParameter() : value_{} {}
  explicit WellKnownParameter(T&& value) : value_(std::forward<T>(value)) {}

  char const* parameter_name() const { return P::well_known_parameter_name(); }
  bool has_value() const { return value_.has_value(); }
  T const& value() const { return value_.value(); }

 private:
  google::cloud::internal::optional<T> value_;
};

template <typename P, typename T>
std::ostream& operator<<(std::ostream& os,
                         WellKnownParameter<P, T> const& rhs) {
  if (rhs.has_value()) {
    return os << rhs.parameter_name() << "=" << rhs.value();
  }
  return os << rhs.parameter_name() << "=<not set>";
}
}  // namespace internal

/**
 * Sets the contentEncoding option for object uploads.
 *
 * The contentEncoding option allows applications to describe how is the data
 * encoded (binary or ASCII) in upload requests.
 */
struct ContentEncoding
    : public internal::WellKnownParameter<ContentEncoding, std::string> {
  using WellKnownParameter<ContentEncoding, std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "contentEncoding"; }
};

/**
 * Defines the `fields` query parameter.
 *
 * The `fields` parameter can be used to limit the fields returned by a request,
 * saving bandwidth and possibly improving performance for applications that do
 * not need a full response from the server.
 *
 * @see
 * https://cloud.google.com/storage/docs/json_api/v1/how-tos/performance#partial-response
 *     for general documentation on how to use this parameter.
 */
struct Fields : public internal::WellKnownParameter<Fields, std::string> {
  using WellKnownParameter<Fields, std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "fields"; }
};

/**
 * Set the version of an object to operate on.
 *
 * For objects in Buckets with `versioning` enabled, the application sometimes
 * needs to specify which version of the object should the request target. This
 * is an optional query parameter to control the version.
 *
 * @see https://cloud.google.com/storage/docs/object-versioning for more
 *     information on GCS Object versioning.
 */
struct Generation
    : public internal::WellKnownParameter<Generation, std::int64_t> {
  using WellKnownParameter<Generation, std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "generation"; }
};

/**
 * A pre-condition: the request succeeds only if the object generation matches.
 *
 * @note Setting this to 0 makes the pre-condition succeed only if there are no
 *     live versions of the object.
 */
struct IfGenerationMatch
    : public internal::WellKnownParameter<IfGenerationMatch, std::int64_t> {
  using WellKnownParameter<IfGenerationMatch, std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "ifGenerationMatch"; }
};

/**
 * A pre-condition: the request succeeds unless the object generation matches.
 *
 * @note When set to 0 the pre-condition succeeds only if there are live
 *    versions of the object.
 */
struct IfGenerationNotMatch
    : public internal::WellKnownParameter<IfGenerationNotMatch, std::int64_t> {
  using WellKnownParameter<IfGenerationNotMatch,
                           std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() {
    return "ifGenerationNotMatch";
  }
};

/**
 * A pre-condition: the request succeeds if the metadata generation matches.
 */
struct IfMetagenerationMatch
    : public internal::WellKnownParameter<IfMetagenerationMatch, std::int64_t> {
  using WellKnownParameter<IfMetagenerationMatch,
                           std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() {
    return "ifMetagenerationMatch";
  }
};

/**
 * A pre-condition: the request succeeds unless the metadata generation matches.
 */
struct IfMetagenerationNotMatch
    : public internal::WellKnownParameter<IfMetagenerationNotMatch,
                                          std::int64_t> {
  using WellKnownParameter<IfMetagenerationNotMatch,
                           std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() {
    return "ifMetagenerationNotMatch";
  }
};

/**
 * A pre-condition: the request succeeds if the source object generation
 * matches.
 *
 * This is only used in CopyObject and RewriteObject operations.
 */
struct IfSourceGenerationMatch
    : public internal::WellKnownParameter<IfSourceGenerationMatch,
                                          std::int64_t> {
  using WellKnownParameter<IfSourceGenerationMatch,
                           std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() {
    return "ifSourceGenerationMatch";
  }
};

/**
 * A pre-condition: the request succeeds unless the source object generation
 * matches.
 */
struct IfSourceGenerationNotMatch
    : public internal::WellKnownParameter<IfSourceGenerationNotMatch,
                                          std::int64_t> {
  using WellKnownParameter<IfSourceGenerationNotMatch,
                           std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() {
    return "ifSourceGenerationNotMatch";
  }
};

/**
 * A pre-condition: the request succeeds if the source object metadata
 * generation matches.
 */
struct IfSourceMetagenerationMatch
    : public internal::WellKnownParameter<IfSourceMetagenerationMatch,
                                          std::int64_t> {
  using WellKnownParameter<IfSourceMetagenerationMatch,
                           std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() {
    return "ifSourceMetagenerationMatch";
  }
};

/**
 * A pre-condition: the request succeeds unless the source object metadata
 * generation matches.
 */
struct IfSourceMetagenerationNotMatch
    : public internal::WellKnownParameter<IfSourceMetagenerationNotMatch,
                                          std::int64_t> {
  using WellKnownParameter<IfSourceMetagenerationNotMatch,
                           std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() {
    return "ifSourceMetagenerationNotMatch";
  }
};

/**
 * Configure the Customer-Managed Encryption Key (CMEK) for an upload.
 *
 * With Customer-Managed Encryption Keys you can use keys generated by Google
 * Cloud's Key Management Service.
 *
 * @see https://cloud.google.com/storage/docs/encryption/customer-managed-keys
 *     for a general introduction to CMEK in GCS.
 */
struct KmsKeyName
    : public internal::WellKnownParameter<KmsKeyName, std::string> {
  using WellKnownParameter<KmsKeyName, std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "kmsKeyName"; }
};

/**
 * Limit the number of results per page when listing Buckets and Objects.
 *
 * Applications may reduce the memory requirements of the Bucket and Object
 * iterators by using smaller page sizes. The downside is that more requests
 * may be needed to iterate over the full range of Buckets and/or Objects.
 */
struct MaxResults
    : public internal::WellKnownParameter<MaxResults, std::int64_t> {
  using WellKnownParameter<MaxResults, std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "maxResults"; }
};

/**
 * Set the ACL to predefined values when creating Buckets or Objects.
 *
 * A predefined ACL is an alias for a set of specific ACL entries that you can
 * use to quickly apply many ACL entries at once to a bucket or object.
 *
 * @see
 * https://cloud.google.com/storage/docs/access-control/lists#predefined-acl for
 * a more detailed description of Predefined ACLs in GCS.
 */
struct PredefinedAcl
    : public internal::WellKnownParameter<PredefinedAcl, std::string> {
  using WellKnownParameter<PredefinedAcl, std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "predefinedAcl"; }
};

/**
 * Set the ACL to a predefined value when copying Objects.
 *
 * A predefined ACL is an alias for a set of specific ACL entries that you can
 * use to quickly apply many ACL entries at once to a bucket or object.
 *
 * @see
 * https://cloud.google.com/storage/docs/access-control/lists#predefined-acl for
 * a more detailed description of Predefined ACLs in GCS.
 */
struct DestinationPredefinedAcl
    : public internal::WellKnownParameter<DestinationPredefinedAcl,
                                          std::string> {
  using WellKnownParameter<DestinationPredefinedAcl,
                           std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() {
    return "destinationPredefinedAcl";
  }
};

/**
 * Set the default object ACL to a predefined value in a Bucket.
 *
 * Every bucket has a default object ACL, and this ACL is applied to all objects
 * uploaded to that bucket without a predefined ACL or an ACL specified in the
 * request.  When creating Buckets it is sometimes convenient to define the
 * default object ACL to one of the predefined values.
 *
 * @see
 * https://cloud.google.com/storage/docs/access-control/lists#defaultobjects for
 * a mode detailed description of default object ACLs.
 *
 * @see
 * https://cloud.google.com/storage/docs/access-control/lists#predefined-acl for
 * a more detailed description of Predefined ACLs in GCS.
 */
struct PredefinedDefaultObjectAcl
    : public internal::WellKnownParameter<PredefinedDefaultObjectAcl,
                                          std::string> {
  using WellKnownParameter<PredefinedDefaultObjectAcl,
                           std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() {
    return "predefinedDefaultObjectAcl";
  }
};

/**
 * Restrict list operations to entries starting with this value.
 *
 * This optional parameter applies to both the request to list objects and to
 * the request that lists buckets.  Setting a value for this option returns
 * only the entries that start with the given prefix.
 */
struct Prefix : public internal::WellKnownParameter<Prefix, std::string> {
  using WellKnownParameter<Prefix, std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "prefix"; }
};

/**
 * Controls what metadata fields are included in the response.
 *
 * For those operations that return the metadata of an Object or Bucket, this
 * option controls if all the fields are returned (using `full`) or if the ACL
 * fields (which can be long) are to be excluded (using `noACL`).
 *
 * Use the `Fields` option for more fine-grained control over the returned
 * fields.
 */
struct Projection
    : public internal::WellKnownParameter<Projection, std::string> {
  using WellKnownParameter<Projection, std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "projection"; }
};

/**
 * Sets the user for this operation for quota enforcement purposes.
 *
 * Google Cloud Platform allows you to set an arbitrary string, up to 40
 * characters long, that identifies a "user" for quota enforcement purposes.
 *
 * @see https://cloud.google.com/apis/docs/capping-api-usage for an introduction
 *     to quotas in Google Cloud Platform.
 */
struct QuotaUser : public internal::WellKnownParameter<QuotaUser, std::string> {
  using WellKnownParameter<QuotaUser, std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "quotaUser"; }
};

/**
 * Set the generation for the source object in copy operations.
 *
 * For objects in Buckets with `versioning` enabled, the application sometimes
 * needs to specify which version of the object should the request target. This
 * is an optional query parameter to control the version of the source object
 * in copy operations.
 *
 * @see https://cloud.google.com/storage/docs/object-versioning for more
 *     information on GCS Object versioning.
 */
struct SourceGeneration
    : public internal::WellKnownParameter<SourceGeneration, std::int64_t> {
  using WellKnownParameter<SourceGeneration, std::int64_t>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "sourceGeneration"; }
};

/**
 * Set the project used for billing in "requester pays" Buckets.
 *
 * GCS Buckets can be configured to charge the requester of an operation for all
 * charges, as opposed to the project that owns the Bucket. Use this parameter
 * when accessing such Buckets to control which project is charged. Note that
 * the caller must have the right permissions in the billed project or the
 * operation would fail.
 *
 * @see https://cloud.google.com/storage/docs/requester-pays for a detailed
 *     description of the requester pays features, which charges are incurred by
 *     the requester, and the exact permissions that you must have to make
 *     such a request.
 */
struct UserProject
    : public internal::WellKnownParameter<UserProject, std::string> {
  using WellKnownParameter<UserProject, std::string>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "userProject"; }
};

/**
 * Control if all versions of an object should be included when listing objects.
 *
 * By default requests listing objects only included the latest (live) version
 * of each object, set this option to `true` to get all the previous versions.
 *
 * @see https://cloud.google.com/storage/docs/object-versioning for more
 *     information on GCS Object versioning.
 */
struct Versions : public internal::WellKnownParameter<Versions, bool> {
  using WellKnownParameter<Versions, bool>::WellKnownParameter;
  static char const* well_known_parameter_name() { return "versions"; }
};

}  // namespace STORAGE_CLIENT_NS
}  // namespace storage
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_WELL_KNOWN_PARAMETERS_H_
