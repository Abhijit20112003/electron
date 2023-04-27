// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_BROWSER_BADGING_BADGE_MANAGER_H_
#define ELECTRON_SHELL_BROWSER_BADGING_BADGE_MANAGER_H_
 

#include <memory>
#include <string>

#include "components/keyed_service/core/keyed_service.h"
#include "mojo/public/cpp/bindings/receiver_set.h"
#include "third_party/abseil-cpp/absl/types/optional.h"
#include "third_party/blink/public/mojom/badging/badging.mojom.h"
#include "url/gurl.h"

namespace content {
class RenderFrameHost;
class RenderProcessHost;
}  // namespace content

namespace badging {

// The maximum value of badge contents before saturation occurs.
constexpr int kMaxBadgeContent = 99;

// Maintains a record of badge contents and dispatches badge changes to a
// delegate.
class BadgeManager : public KeyedService, public blink::mojom::BadgeService {
 public:
  BadgeManager();
  ~BadgeManager() override;

  // disable copy
  BadgeManager(const BadgeManager&) = delete;
  BadgeManager& operator=(const BadgeManager&) = delete;

  static void BindFrameReceiver(
      content::RenderFrameHost* frame,
      mojo::PendingReceiver<blink::mojom::BadgeService> receiver);
  static void BindServiceWorkerReceiver(
      content::RenderProcessHost* service_worker_process_host,
      const GURL& service_worker_scope,
      mojo::PendingReceiver<blink::mojom::BadgeService> receiver);

  // Determines the text to put on the badge based on some badge_content.
  static std::string GetBadgeString(absl::optional<int> badge_content);

 private:
  // The BindingContext of a mojo request. Allows mojo calls to be tied back
  // to the execution context they belong to without trusting the renderer for
  // that information.  This is an abstract base class that different types of
  // execution contexts derive.
  class BindingContext {
   public:
    virtual ~BindingContext() = default;
  };

  // The BindingContext for Window execution contexts.
  class FrameBindingContext final : public BindingContext {
   public:
    FrameBindingContext(int process_id, int frame_id)
        : process_id_(process_id), frame_id_(frame_id) {}
    ~FrameBindingContext() override = default;

    int GetProcessId() { return process_id_; }
    int GetFrameId() { return frame_id_; }

   private:
    int process_id_;
    int frame_id_;
  };

  // The BindingContext for ServiceWorkerGlobalScope execution contexts.
  class ServiceWorkerBindingContext final : public BindingContext {
   public:
    ServiceWorkerBindingContext(int process_id, const GURL& scope)
        : process_id_(process_id), scope_(scope) {}
    ~ServiceWorkerBindingContext() override = default;

    int GetProcessId() { return process_id_; }
    GURL GetScope() { return scope_; }

   private:
    int process_id_;
    GURL scope_;
  };

  // blink::mojom::BadgeService:
  // Note: These are private to stop them being called outside of mojo as they
  // require a mojo binding context.
  void SetBadge(blink::mojom::BadgeValuePtr value) override;
  void ClearBadge() override;

  // All the mojo receivers for the BadgeManager. Keeps track of the
  // render_frame the binding is associated with, so as to not have to rely
  // on the renderer passing it in.
  mojo::ReceiverSet<blink::mojom::BadgeService, std::unique_ptr<BindingContext>>
      receivers_;

  // Delegate which handles actual setting and clearing of the badge.
  // Note: This is currently only set on Windows and MacOS.
  // std::unique_ptr<BadgeManagerDelegate> delegate_;
};

}  // namespace badging

#endif  // ELECTRON_SHELL_BROWSER_BADGING_BADGE_MANAGER_H_

// End of generated file from components/components_badging.mojom.h
// Location: components/badging/

#endif  // SHELL_BROWSER_BADGING_BADGE_MANAGER_H_

// End of generated header from ../../shell/browser/badging/badge_manager.h
// Location: electron/shell/browser/badging/

namespace electron { namespace api { namespace badging {  // NOLINT(build/namespaces)

class BadgeManager : public mate::EventEmitter<BadgeManager> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 private:
  explicit BadgeManager(v8::Isolate* isolate);
  ~BadgeManager() override;

  // mate::Wrappable:
  mate::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate) override;

  // blink::mojom::BadgeService:
  void SetBadge(blink::mojom::BadgeValuePtr value) override;
  void ClearBadge() override;

  // The BindingContext of a mojo request. Allows mojo calls to be tied back
  // to the execution context they belong to without trusting the renderer for
  // that information.  This is an abstract base class that different types of
  // execution contexts derive.
  class BindingContext {
   public:
    virtual ~BindingContext() = default;
  };

  // The BindingContext for Window execution contexts.
  class FrameBindingContext final : public BindingContext {
   public:
    FrameBindingContext(int process_id, int frame_id)
        : process_id_(process_id), frame_id_(frame_id) {}
    ~FrameBindingContext() override = default;

    int GetProcessId() { return process_id_; }
    int GetFrameId() { return frame_id_; }

   private:
    int process_id_;
    int frame_id_;
  };

  // The BindingContext for ServiceWorkerGlobalScope execution contexts.
  class ServiceWorkerBindingContext final : public BindingContext {
   public:
    ServiceWorkerBindingContext(int process_id, const GURL& scope)
        : process_id_(process_id), scope_(scope) {}
    ~ServiceWorkerBindingContext() override = default;

    int GetProcessId() { return process_id_; }
    GURL GetScope() { return scope_; }

   private:
    int process_id_;
    GURL scope_;
  };

  // All the mojo receivers for the BadgeManager. Keeps track of the
  // render_frame the binding is associated with, so as to not have to rely
  // on the renderer passing it in.
  mojo::ReceiverSet<blink::mojom::BadgeService, std::unique_ptr<BindingContext>>
      receivers_;

  // Delegate which handles actual setting and clearing of the badge.
  // Note: This is currently only set on Windows and MacOS.
