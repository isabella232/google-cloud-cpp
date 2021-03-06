// Copyright 2020 Google LLC
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

#include "google/cloud/pubsub/subscriber_options.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace pubsub {
inline namespace GOOGLE_CLOUD_CPP_PUBSUB_NS {
namespace {

TEST(SubscriberOptionsTest, Default) {
  SubscriberOptions const options{};
  EXPECT_LT(0, options.max_outstanding_messages());
  EXPECT_LT(0, options.max_outstanding_bytes());
  EXPECT_LE(options.concurrency_lwm(), options.concurrency_hwm());
  EXPECT_LT(0, options.concurrency_hwm());
}

TEST(SubscriberOptionsTest, SetMessageCount) {
  auto options = SubscriberOptions{}.set_max_outstanding_messages(16);
  EXPECT_EQ(16, options.max_outstanding_messages());

  options.set_max_outstanding_messages(-7);
  EXPECT_EQ(0, options.max_outstanding_messages());
}

TEST(SubscriberOptionsTest, SetBytes) {
  auto options = SubscriberOptions{}.set_max_outstanding_bytes(16 * 1024);
  EXPECT_EQ(16 * 1024, options.max_outstanding_bytes());

  options.set_max_outstanding_bytes(-7);
  EXPECT_EQ(0, options.max_outstanding_bytes());
}

TEST(SubscriberOptionsTest, SetConcurrency) {
  auto options = SubscriberOptions{}.set_concurrency_watermarks(8, 16);
  EXPECT_EQ(16, options.concurrency_hwm());
  EXPECT_EQ(8, options.concurrency_lwm());

  options.set_concurrency_watermarks(0, 0);
  EXPECT_EQ(1, options.concurrency_hwm());
  EXPECT_EQ(0, options.concurrency_lwm());

  options.set_concurrency_watermarks(10, 5);
  EXPECT_EQ(5, options.concurrency_hwm());
  EXPECT_EQ(5, options.concurrency_lwm());
}

}  // namespace
}  // namespace GOOGLE_CLOUD_CPP_PUBSUB_NS
}  // namespace pubsub
}  // namespace cloud
}  // namespace google
